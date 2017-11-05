
# Ballance Project Recode


## 2017年10月26日 星期四

### 1. 项目启动

### 2. 项目准备
* Win10系统
* Qt开发环境
* 云服务器

### 3. 项目进展
* **创建**主界面类`Ballance : public QWidget`
	+ 搭建主要的菜单界面
* **创建**保存地图的类`CBallancePath`


## 2017年10月27日 星期五

### 项目进展
* 创建综合头文件ylqtwidgetheader.h
* **创建**游戏界面类`BallancepathOpenglWidget : public QGLWidget`
	+ 画出简单的图形（二维和三维）并上色
* 分离键盘事件


## 2017年10月28日 星期六


## 2017年10月29日 星期日


## 2017年10月30日 星期一
* `BallancepathOpenglWidget : public QGLWidget`
	+ 图形贴图
	+ 画Ball，研究其旋转属性


## 2017年10月31日 星期二

### 1. 项目准备
* 创建GitHub仓库
* 完善项目目录结构

### 2. 项目进展
* `BallancepathOpenglWidget : public QGLWidget`
	+ Ball贴图、旋转
* **创建**我的画家类`YLOpenGLPainter`
	+ 整理现阶段能够画出的图形为静态方法


## 2017年11月01日 星期三

### 项目进展
* `BallancepathOpenglWidget : public QGLWidget`
	+ 构建三维坐标系，在XoY平面中滚动Ball
	+ 构建观察点，使其与Ball的平移分量相对静止


## 2017年11月02日 星期四

### 项目进展
* `BallancepathOpenglWidget : public QGLWidget`
	+ 规范三维坐标系
	+ 使用定时器处理四向按键，使移动事件更加灵活，并能够斜方向滚动
	+ 计算旋转弧度与移动距离，使Ball更加真实
* `CBallancePath`
	+ 从基于STM32的Ballance项目移植map计算规则
* **创建**四向地图（四叉树）类模板`YLTree4`


## 2017年11月3日 星期五

### 1. 项目进展
* `YLTree4`
	+ 完成四叉树扩展（添加结点）、遍历等基本方法编写
* `CBallancePath`
	+ 使用四叉树计算地图

### 2. Bug
* `YLTree4` 遍历树的方法的参数
	+ lambda函数作为类模板的方法的参数如何定义


## 2017年11月4日 星期六


## 2017年11月5日 星期日

### 1. Bug解决
* `YLTree4` 遍历树的方法的参数
	+ 模板类中嵌套模板函数即可使lambda函数作为类模板的方法的参数

### 2. 项目进展
* `CBallancePath`
	+ 完善map计算规则
	+ 向controller提供接口





# ====================================


# Ballance Project 更新频率


## 2017年10月31日 ———— 2017年11月01日
学习GitHub使用方法


## 2017年11月02日 ———— 至今
工作日每天晚上10点左右更新代码，周末不定时更新





# ====================================
