import React, { Widget, WidgetProps } from "@lcui/react";
import "./toggle-button.scss";

export default function ToggleButton(props: WidgetProps) {
  return <Widget className="toggle-button" {...props} />;
}
