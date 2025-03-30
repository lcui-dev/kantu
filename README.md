# KanTu

KanTu, a lightweight image viewer.

> Do you want to know the development process of this program? View this course: https://leanpub.com/c/lcui-image-viewer

[中文](README.zh-cn.md)/**English**

![preview](./preview.jpg)

## Features

- Supported formats: PNG, JPEG, BMP
- Functions: Zoom, fullscreen mode, view image details

## Technical Implementation

This is a sample project built with the [LCUI Library](https://github.com/lc-soft/LCUI), which demonstrates:

- How to develop LCUI applications
- LCUI's CSS and layout capabilities
- LCUI's GUI rendering performance
- LCUI development tools
- How to separate business logic from GUI
- How to traverse directories and read image file information
- How to implement image display and zoom using CSS styles
- How to use icons from an icon library to decorate UI
- How to write LCUI components using TypeScript
- How to integrate TailwindCSS into a project to improve CSS efficiency

## Installation

Go to the [Releases page](https://github.com/lcui-dev/kantu/releases) to download the binary package. Extract it to your desired installation directory and set the executable file of "KanTu" as the default program for opening image files.

## Roadmap

- Optimize memory usage: thumbnail lazy loading, cache eviction strategies
- Improve rendering performance
- Support more formats
- Light/Dark theme switching
- Package into an installer with configurable format associations during installation

## Development

This project is written in C, with the GUI implemented using the [LCUI](https://github.com/lc-soft/LCUI) library. Some parts of the UI code adopt popular web frontend technologies, including TypeScript, React, Sass, and TailwindCSS.

To develop based on this project, you need the following software installed:

- [Node.js](https://nodejs.org/en): JavaScript runtime environment for running development tools.
- [Xmake](https://xmake.io/): A build tool for C/C++ projects.
- [lcui-cli](https://github.com/lcui-dev/lcui-cli): LCUI's development tools. Requires Node.js. Install it by running `npm install -g @lcui/cli` after setting up Node.js.

Clone the project repository:

```sh
git clone https://gitee.com/lcui-dev/kantu.git
```

Enter the project directory and sync submodules:

```sh
cd kantu
git submodule sync --recursive
git submodule update --init --recursive
```

Install dependencies:

```sh
npm install
```

Build the project:

```sh
lcui build
```

Run the project:

```sh
xmake run
```

### Directory Structure

- **`.lcui/`**: Cache directory for LCUI development tools.
- **`.xmake/`**: Cache directory for Xmake.
- **`build/`**: Build directory containing generated files during the build process.
- **`dist/`**: Distribution directory where built resources are output.
- **`node_modules/`**: Directory for Node.js modules required by development tools.
- **`src/`**: Source code directory.
  - **`assets/`**: Directory for resource files.
  - **`file-info-panel.tsx`**: File info panel component.
  - **`file-info-reader.c`**: File info reader.
  - **`film-view.tsx`**: Film view component.
  - **`global.css`**: Global styles.
  - **`home.tsx`**: Main UI.
  - **`image-collector.c`**: Image file collector.
  - **`image-controller.c`**: Image zoom controller.
  - **`image-view.tsx`**: Image view component.
  - **`main.c`**: Application entry point.
  - **`slider.tsx`**: Slider component.
  - **`toggle-button.tsx`**: Toggle button component.
  - **`utils.c`**: Utility functions.
  - **`*.scss`**: Style files.
  - **`*.scss.h`**, **`*.css.h`**, **`*.tsx.h`**: Compiled source files in C from respective file types.
  - **`*.c`**: C source files.
  - **`*.h`**: C header files.
- **`vendor/`**: Source directory for third-party libraries.
- **`vendor.node_modules/`**: Output directory for Node.js module compilation.
- **`clang-format`**: Code formatting configuration.
- **`LICENSE`**: License file.
- **`package.json`**: Node.js project configuration file.
- **`package-lock.json`**: Dependency manifest for Node.js projects.
- **`postcss.config.js`**: [PostCSS](https://postcss.org/) configuration file.
- **`tailwind.config.js`**: [TailwindCSS](https://tailwindcss.com/) configuration file.

## Contribution

- **Issue reporting and suggestions**: Submit issues on the [Issues page](https://github.com/lcui-dev/kantu/issues/new). Make sure to provide detailed descriptions.
- **Code contribution**: Before contributing, [submit an issue](https://github.com/lcui-dev/kantu/issues/new) to describe the changes and implementation plan. This ensures compatibility with the project's direction.

## License

[MIT](./LICENSE.TXT)
