import React, { Text, Widget } from "@lcui/react";
import {
  Image,
  TriangleLeftFilled,
  TriangleRightFilled,
  ZoomOut,
  ZoomIn,
  ArrowMaximize,
  PageFit,
  PageFitFilled,
  Save,
  ResizeImage,
  TableBottomRow,
  TableBottomRowFilled,
  Info,
} from "@lcui/react-icons";
import "@lcui/react-icons/dist/style.css";
import Slider from "./slider";
import ToggleButton from "./toggle-button";
import FileInfoPanel from "./file-info-panel";
import "./image-view.scss";
import "./global.css";

export default function ImageView() {
  return (
    <Widget className="image-view flex bg-[#1f1f1f] w-full h-full">
      <Widget className="flex h-full flex-auto flex-col">
        <Widget className="progress">
          <Widget $ref="progressbar" className="bar" />
        </Widget>
        <Widget
          $ref="content"
          className="flex-auto flex items-center justify-center"
        >
          <Widget $ref="tip" className="tip">
            <Image className="icon" fontSize={80} />
            <Text $ref="filename" />
            <Text>似乎不支持此文件格式。</Text>
          </Widget>
        </Widget>
        <Widget $ref="prev" className="switch-button prev">
          <TriangleLeftFilled />
        </Widget>
        <Widget $ref="next" className="switch-button next">
          <TriangleRightFilled />
        </Widget>
        <Widget className="toolbar">
          <ToggleButton className="button">
            <TableBottomRow className="icon" />
            <TableBottomRowFilled className="icon" />
          </ToggleButton>
          <Widget className="divider" />
          <Info
            className="icon button mr-1"
            onClick="image_view_open_file_info_panel"
          />
          <Widget className="file-info mr-auto opacity-50 flex border-l border-l-white h-4 items-center pl-3">
            <ResizeImage className="mr-2 text-lg" fontSize={14} />
            <Text $ref="image_size" className="mr-4" />
            <Save className="m-2" fontSize={14} />
            <Text $ref="file_size" />
          </Widget>
          <Text $ref="percentage" className="percentage">
            100%
          </Text>
          <Widget $ref="fit" className="button fit-button">
            <PageFit className="icon icon-fit" />
            <PageFitFilled className="icon icon-fit-fill" />
          </Widget>
          <ZoomOut $ref="zoom_out" className="icon button" />
          <Slider $ref="slider" />
          <ZoomIn $ref="zoom_in" className="icon button" />
          <Widget className="divider" />
          <ArrowMaximize $ref="maximize" className="icon button" />
        </Widget>
      </Widget>
      <FileInfoPanel
        $ref="file_info_panel"
        className="flex-none w-[360px] h-full"
      />
    </Widget>
  );
}
