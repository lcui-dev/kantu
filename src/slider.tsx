import React, {
  CType,
  fmt,
  useState,
  Widget,
  WidgetProps,
} from "@lcui/react";

export default function Slider(props: WidgetProps) {
  const [percentage] = useState(0, CType.Double);

  return (
    <Widget
      className="flex items-center px-[9px] h-[40px]"
      onMouseDown="slider_on_mousedown"
      onMouseMove="slider_on_mousemove"
      onMouseUp="slider_on_mouseup"
      {...props}
    >
      <Widget className="w-full h-[4px] rounded-[4px] bg-slate-500">
        <Widget
          $ref="bar"
          className="h-full bg-sky-500"
          style={{ width: fmt(percentage, "%") }}
        />
      </Widget>
      <Widget
        $ref="thumb"
        className="absolute top-[50%] -mt-[9px] w-[18px] h-[18px] rounded-[9px] border-[4px] bg-sky-500 border-slate-600 hover:border-[3px]"
      />
    </Widget>
  );
}

Slider.displayName = "slider";
