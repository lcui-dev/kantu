import React, { Text, Widget } from "@lcui/react";
import pkg from "../package.json";
import "./home.scss";

export default function Home() {
  return (
    <Widget className="home">
      <Widget className="container">
        <Widget className="header">
          <Widget className="logo" />
          <Text className="name">{pkg.name}</Text>
          <Text className="version">版本：{pkg.version}</Text>
          <Text className="description">{pkg.description}</Text>
        </Widget>
        <Text className="usage">
          用法：右键单击图片文件 -&gt; 打开方式 -&gt; 选择其他应用 -&gt; 选择{" "}
          {pkg.name}
        </Text>
      </Widget>
    </Widget>
  );
}
