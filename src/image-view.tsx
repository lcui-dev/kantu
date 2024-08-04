import React, { Text, Widget } from "@lcui/react";
import {
  Image,
  ZoomOut,
  ZoomIn,
  ArrowMaximize,
  RatioOneToOne,
  Screenshot,
  TriangleLeftFilled,
  TriangleRightFilled,
} from "@lcui/react-icons";
import "@lcui/react-icons/dist/style.css";
import "./image-view.scss";

export default function ImageView() {
  return (
    <Widget className="image-view">
      <Widget className="progress">
        <Widget $ref="progressbar" className="bar" />
      </Widget>
      <Widget $ref="content" className="content">
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
        <Text $ref="percentage" className="percentage">
          100%
        </Text>
        <ZoomOut $ref="zoom_out" className="icon button" />
        <ZoomIn $ref="zoom_in" className="icon button" />
        <Screenshot $ref="fill" className="icon button" />
        <RatioOneToOne $ref="original" className="icon button" />
        <Widget className="divider" />
        <ArrowMaximize $ref="maximize" className="icon button" />
      </Widget>
    </Widget>
  );
}
