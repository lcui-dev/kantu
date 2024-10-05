import React, { Link, Text, Widget, WidgetProps } from "@lcui/react";
import {
  Image,
  CalendarLtr,
  ResizeImage,
  FolderOpen,
  Dismiss,
} from "@lcui/react-icons";
import "./file-info-panel.scss";

export default function FileInfoPanel(props: WidgetProps) {
  const fields = [
    {
      icon: <Image />,
      control: <Text $ref="name" className="field-label" />,
    },
    {
      icon: <CalendarLtr />,
      control: <Text $ref="datetime" className="field-value" />,
    },
    {
      icon: <ResizeImage />,
      control: (
        <Widget>
          <Text className="field-label mb-1">大小信息</Text>
          <Text className="field-value" $ref="size"></Text>
        </Widget>
      ),
    },
    {
      icon: <FolderOpen />,
      control: (
        <Widget>
          <Text className="field-label mb-1">文件路径</Text>
          <Link
            className="field-value text-sky-500 hover:text-sky-700"
            $ref="path"
          ></Link>
        </Widget>
      ),
    },
  ];
  return (
    <Widget
      className="file-info-panel hidden border-t border-l border-l-black p-4 rounded-l"
      {...props}
    >
      <Text className="mb-6 text-xl font-bold">信息</Text>
      <Dismiss
        fontSize={20}
        className="absolute top-4 right-4 opacity-70 hover:opacity-100"
        onClick="file_info_panel_close"
      />
      {fields.map((field, index) => (
        <Widget key={index} className="flex mb-4">
          <Widget className="flex-none field-icon">{field.icon}</Widget>
          <Widget className="flex-auto pl-4">{field.control}</Widget>
        </Widget>
      ))}
    </Widget>
  );
}

FileInfoPanel.displayName = "file_info_panel";
