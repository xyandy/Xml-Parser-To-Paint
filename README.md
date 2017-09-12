# 基于xml格式的图形显示 

## 1. 开发环境：
Windows 

## 2. 主要内容：
利用Qt开发界面，通过解析xml文件，生成各类复杂图形，并且支持图形变换，缩放，平移

## 3. 项目详情：
主要包括4个模块：
1. **readXml模块**，利用QDomDocument将xml文本序列化存储到自定义类readXml中
2. **ParseXml模块**：解析嵌套公式获取图形参数，生成多种图形路径存储到PainterPath
3. **PainterWindow模块**：根据路径生成图形（包括图形的大小，位置，填充，描边，缩放等）
4. **Project模块**：负责用户交互，包括各种控件位置布局，以及他们对应的触发事件（信号槽机制）

## 4. 效果如下：

 ![image1](https://github.com/xyandy/XmlParserToPaint/blob/master/1.png)
 
 ![image2](https://github.com/xyandy/XmlParserToPaint/blob/master/2.png)
 
 ![image3](https://github.com/xyandy/XmlParserToPaint/blob/master/3.png)
