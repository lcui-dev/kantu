# 看图

看图（KanTu），一个轻量级的图片查看器。

> 想了解此程序的开发过程？查看此实战课程：https://leanpub.com/c/lcui-image-viewer

**中文**/[English](./README.md)

![preview](./preview.jpg)

## 功能特性

- 支持格式：png、jpeg、bmp
- 功能：缩放、全屏模式、查看图片信息

## 技术实现

这是 [LCUI 开发库](https://github.com/lc-soft/LCUI) 的一个示例项目，你可以从中了解到：

- LCUI 应用程序的开发方法
- LCUI 的 CSS 和布局能力
- LCUI 的图形界面渲染性能
- LCUI 开发工具的能力
- 如何将业务逻辑与界面分离
- 如何遍历文件目录、读取图片文件信息
- 如何基于 CSS 样式实现图片的显示和缩放
- 如何使用图标库中的图标装饰界面
- 如何使用 TypeScript 语言编写 LCUI 组件
- 如何在项目中引入 TailwindCSS 来提高 CSS 样式编写效率

## 安装

前往 [Releases 页面](https://github.com/lcui-dev/kantu/releases)下载二进制文件包，将其解压到你指定的安装目录，然后设置图片文件的打开方式为"看图"的可执行文件。

## 路线图

- 优化内存占用：缩略图懒加载、缓存淘汰策略
- 优化渲染性能
- 支持更多格式
- 深色/浅色主题切换
- 打包成安装包，在安装时可选择关联的格式

## 开发

本项目采用 C 语言编写，图形界面基于 [LCUI](https://github.com/lc-soft/LCUI) 库实现，界面的部分代码采用了 Web 前端领域流行的开发技术编写，包括 TypeScript、React、Sass、TailwindCSS。

要基于该项目进行开发，你需要先安装以下软件：

- [Node.js](https://nodejs.org/zh-cn): JavaScript 运行时环境，用于运行开发工具。
- [Xmake](https://xmake.io/): C/C++ 项目的构建工具。
- [lcui-cli](https://github.com/lcui-dev/lcui-cli): LCUI 的开发工具，依赖 Node.js 环境，在安装完 Node.js 后执行命令 `npm install -g @lcui/cli` 安装。

下载本项目的代码库：

```sh
git clone https://gitee.com/lcui-dev/kantu.git
```

进入项目目录，同步子模块：

```sh
cd kantu
git submodule sync --recursive
git submodule update --init --recursive
```

安装依赖包：

```sh
npm install
```

构建：

```sh
lcui build
```

运行：

```sh
xmake run
```

### 目录结构

- **`.lcui/`**: LCUI 开发工具的缓存目录。
- **`.xmake/`**: XMake 的缓存目录。
- **`build/`**: 构建目录，包含构建过程中产出的文件。
- **`dist/`**: 发布目录，构建后的资源文件都会输出到这里。
- **`node_modules/`**: Node.js 模块目录，包含开发工具依赖的各种模块。
- **`src/`**: 源码目录。
    - **`assets/`**: 资源文件目录。
    - **`file-info-panel.tsx`**: 文件信息面板组件。
    - **`file-info-reader.c`**: 文件信息读取器。
    - **`film-view.tsx`**: 影片视图组件。
    - **`global.css`**: 全局样式。
    - **`home.tsx`**: 主界面。
    - **`image-collector.c`**: 图片文件收集器。
    - **`image-controller.c`**: 图片缩放控制器。
    - **`image-view.tsx`**: 图片查看界面组件。 
    - **`main.c`**: 应用程序主入口。
    - **`slider.tsx`**: 滑块组件。
    - **`toggle-button.tsx`**: 切换按钮组件。
    - **`utils.c`**: 实用工具函数集。
    - **`*.scss`**: 样式文件。
    - **`*.scss.h`**: 已编译为 C 源码的 `.scss` 文件。
    - **`*.css.h`**: 已编译为 C 源码的 `.css` 文件。
    - **`*.tsx.h`**: 已编译为 C 源码的 `.tsx` 文件。
    - **`*.c`**: C 源文件。
    - **`*.h`**: C 头文件。
- **`vendor/`**: 第三方库的源码目录。
- **`vendor.node_modules/`**: Node.js 模块的编译输出目录。
- **`clang-format`**: 代码格式化工具的配置文件。
- **`LICENSE`**: 许可证文件。
- **`package.json`**: Node.js 项目配置文件。
- **`package-lock.json`**: Node.js 项目的依赖项清单文件。
- **`postcss.config.js`**: [PostCSS](https://postcss.org/) 配置文件。
- **`tailwind.config.js`**: [TailwindCSS](https://tailwindcss.com/) 配置文件。

## 贡献

- 反馈问题和建议：在 [Issues](https://github.com/lcui-dev/kantu/issues/new) 页面提交，务必描述清楚。
- 贡献代码：请先[提交 issue](https://github.com/lcui-dev/kantu/issues/new)，在 issue 中描述你要改的内容和实现方案，以确认你的方案是否可行、是否与项目发展路线冲突。

## 许可

[MIT](./LICENSE.TXT)
