import React, {
  ScrollArea,
  ScrollAreaContent,
  Scrollbar,
  WidgetProps,
} from "@lcui/react";
import "./film-view.scss";

export default function FilmView(props: WidgetProps) {
  return (
    <ScrollArea className="film-view hidden" {...props}>
      <ScrollAreaContent $ref="content" className="film-view-content" />
      <Scrollbar orientation="horizontal" />
    </ScrollArea>
  );
}

FilmView.displayName = "film_view";
