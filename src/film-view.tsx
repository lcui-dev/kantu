import React, { Scrollbar, Widget, WidgetProps } from "@lcui/react";
import "./film-view.scss";

export default function FilmView(props: WidgetProps) {
  return (
    <Widget className="film-view hidden" {...props}>
      <Widget $ref="content" id="filmViewContent" className="film-view-content" />
      <Scrollbar direction="horizontal" target="filmViewContent" />
    </Widget>
  );
}

FilmView.displayName = "film_view";
