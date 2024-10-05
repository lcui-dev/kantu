import React, { Widget, WidgetProps } from "@lcui/react";
import "./slider.scss";

export default function Slider(props: WidgetProps) {
  return (
    <Widget className="slider" {...props}>
      <Widget className="slider-track">
        <Widget $ref="bar" className="bg-blue-500" />
      </Widget>
      <Widget $ref="thumb" className="slider-thumb" />
    </Widget>
  );
}
