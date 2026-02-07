import os
import json
from pathlib import Path
from PIL import Image

import cv2

# gradio==5.18
import gradio as gr

# gradio_bbox_annotator==0.1.1
from gradio_bbox_annotator import BBoxAnnotator


def generate_relearning_dataset(image_path, bboxes, image_lable):
    name = os.path.basename(image_path)
    image = cv2.imread(image_path)
    height, weight = image.shape[:2]

    sample = {
        name: {
            "data_properties": {
                "height": height,
                "weight": weight
            },
            "other_infomation":{},
            "data_source":"simulation",
            "data_source_description":"\u4eff\u771f\u5688\u6837\u672c",
            "lable":{
                "detection": []
            }
        }
    }

    for i, bbox in enumerate(bboxes):
        x1, y1, x4, y4, _ = bbox
        x2 = abs(x1 - x4)
        y2 = y1
        x3 = x1
        y3 = abs(y1 - y4)

        detection = {
            "id": i,
            "bbox": [x1, y1, x2, y2, x3, y3, x4, y4],
            "classification": image_lable,
            "confidence": 1,
            "is_manual_label": 1
        }

        sample[name]["lable"]["detection"].append(detection)

    data_set_path = './test_data_set.json'
    path = Path(data_set_path)

    if not path.exists():
        path.touch()

        origin_data_set = {
            "dataset_format": "relearning",
            "dataset_name": "sar_dataset",
            "dataset_description": "relearning",
            "labeldescription": {
                "bbox": "",
                "classification": {
                    "0": "class0",
                    "1": "class1",
                    "2": "class2",
                    "3": "class3",
                    "4": "class4",
                    "5": "class5"
                }
            },
            "sample": {
                
            }
        }
    else:
        with open(data_set_path, 'r', encoding='utf-8') as f:
            origin_data_set = json.load(f)
    
    origin_data_set["sample"][name] = sample[name]
    with open(data_set_path, 'w', encoding='utf-8') as f:
        json.dump(origin_data_set, f, indent=4, ensure_ascii=False)


# 标注图片处理
def process_annotation(annotation_info, annotation_lable, preview_image_path, upload_preview_image_list):
    annotation_image_path = annotation_info[0]
    annotation_bboxes = annotation_info[1]

    # 生成relearning_dataset
    generate_relearning_dataset(annotation_image_path, annotation_bboxes, annotation_lable)

    # original = cv2.imread(annotation_image_path)
    original = cv2.imread(preview_image_path)
    if original is None:
        return None, "无有效图片"
    
    drawn_image = cv2.cvtColor(original, cv2.COLOR_BGR2RGB)
    for bbox in annotation_bboxes:
        x_min, y_min, x_max, y_max, _ = bbox
        # cropped_image = drawn_image[y_min:y_max, x_min:x_max]
        cv2.rectangle(drawn_image, (x_min, y_min), (x_max, y_max), (255,0,0), 2)
        cv2.putText(drawn_image, annotation_lable, (x_min, y_min-10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,0,0), 1)

    data_text = "\n".join([str(b) for b in annotation_bboxes])   
    return drawn_image, data_text


# 上传所有标注图片信息
def upload_all_annotators_info(*args):
    bbox_annotators = args[:8]
    lables = args[8:]
    # 上传的所有图片
    files = args[-1]

    # 样例图片数据
    origin_image_list = []
    for path in files:
        data = cv2.imread(path)
        origin_image_list.append(data)

    # 标注图片数据
    annotators_image_list = []
    for i in range(8):
        if bbox_annotators[i] and lables[i]:
            image_path, bboxes = bbox_annotators[i]
            data = cv2.imread(image_path)
            bbox_list = []
            for bbox in bboxes:
                x1, y1, x2, y2, _ = bbox
                bbox_list.append([x1, y1, x2, y2, lables[i]])

            annotate_image = AnnotateImage(data, bbox_list)
            annotators_image_list.append(annotate_image)

    return origin_image_list, annotators_image_list


class AnnotateImage:
    def __init__(self, data: cv2.typing.MatLike, bboxes):
        self.data = data
        self.bboxes = bboxes


class PreviewImage:
    def __init__(self, path):
        self.name = Path(path).name
        self.temp_path = path
        self.is_annotated = False
        self.annotator_bboxes = []
        self.origin_data = Image.open(self.temp_path)
        self.annotator_data = self.origin_data.copy()


class ImageManager:
    def __init__(self):
        self.preview_image_list = []
        self.name_to_path = {}

    def add_images(self, files):
        temp_path = [f.name for f in files]
        for path in temp_path:
            name = Path(path).name
            self.name_to_path[name] = path

        for path in temp_path:
            self.preview_image_list.append(PreviewImage(path))

    def get_preview_image_name_list(self):
        res = []
        for image in self.preview_image_list:
            res.append(image.name)
        return res

    def get_preview_image_path_list(self):
        res = []
        for image in self.preview_image_list:
            res.append(image.temp_path)
        return res


with gr.Blocks(title="一体化标注工具", theme=gr.themes.Soft()) as demo:
    state = gr.State(ImageManager())

    bbox_annotators = []
    annotator_lables = []
    submit_btns = []
    clear_btns = []
    # preview_images = []
    # annotator_datas = []

    origin_image_list = []
    annotators_image_list = []


    def handle_upload(files, manager: ImageManager):
        if not files:
            return gr.Radio(), None

        manager.add_images(files)
        name_list = manager.get_preview_image_name_list()
        path_list = manager.get_preview_image_path_list()

        return gr.Radio(choices=name_list, value=name_list[0]), path_list[0]

    def handle_selection(selected_file, manager: ImageManager):
        path = manager.name_to_path[selected_file]

        for image in manager.preview_image_list:
            if selected_file == image.name:
                return image.origin_data, image.annotator_data
    
    with gr.Row():
        with gr.Column(scale=1, min_width=200):
            preview_image = gr.Image(
                label="图片预览",
                interactive=False,
                height=500,
                sources=None,
                type="filepath"
            )

        with gr.Column(scale=1, min_width=200):
            upload_button = gr.File(
                label="📁 选择文件夹",
                file_count="directory",
                file_types=["image"]
            )

            preview_image_list = gr.Radio(
                label="图片列表",
                choices=[],
                interactive=True
            )
    
    with gr.Row():
        with gr.Column(scale=1):
            with gr.Tabs() as annotator_tabs:
                for i in range(8):
                    with gr.Tab(f"视觉提示 {i+1}") as tab:
                        bbox_annotator = BBoxAnnotator(
                            label="点击或拖放图片到此区域", 
                            categories=[""]
                        )

                        lable_box = gr.Textbox(label="输入类别", placeholder="在这里输入内容...")
            
                        with gr.Row():
                            submit_btn = gr.Button("查看预览", variant="huggingface")
                            clear_btn = gr.Button("清空画布", variant="secondary")

                        bbox_annotators.append(bbox_annotator)
                        annotator_lables.append(lable_box)
                        submit_btns.append(submit_btn)
                        clear_btns.append(clear_btn)
            
            with gr.Row():
                add_btn = gr.Button("提交所有标注", variant="primary")
            
        with gr.Column(scale=1):
            annotator_image = gr.Image(
                label="标注预览",
                interactive=False,
                height=500
            )

            annotator_data = gr.Textbox(
                label="标注数据",
                lines=8
            )                

    for i in range(8):
        submit_btns[i].click(
            fn=process_annotation,
            inputs=[bbox_annotators[i], annotator_lables[i], preview_image, preview_image_list],
            outputs=[annotator_image, annotator_data]
        )    
    
        clear_btns[i].click(
            fn=lambda: (None, ""),
            outputs=[bbox_annotators[i], annotator_data]
        )

    # preview_image.change(
    #     fn=lambda img: (img),
    #     inputs=[preview_image],
    #     outputs=[bbox_annotator]
    # )

    upload_button.upload(
        fn=handle_upload,
        inputs=[upload_button, state],
        outputs=[preview_image_list, preview_image]
    )

    preview_image_list.select(
        fn=handle_selection,
        inputs=[preview_image_list, state],
        outputs=[preview_image, annotator_image]
    )

    add_btn.click(
        fn=upload_all_annotators_info,
        inputs=[bbox_annotators[0], bbox_annotators[1], bbox_annotators[2], bbox_annotators[3], 
                bbox_annotators[4], bbox_annotators[5], bbox_annotators[6], bbox_annotators[7], 
                annotator_lables[0], annotator_lables[1], annotator_lables[2], annotator_lables[3], 
                annotator_lables[4], annotator_lables[5], annotator_lables[6], annotator_lables[7], 
                upload_button],
        outputs=[]
    ).then(
        fn=lambda: gr.Success("操作成功!"),
        outputs=[]
    )


if __name__ == "__main__":
    demo.launch(server_name="127.0.0.1", server_port=7862, debug=True)