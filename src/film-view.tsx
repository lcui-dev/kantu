import {
  ScrollArea,
  ScrollAreaContent,
  Scrollbar,
  WidgetProps,
} from "@lcui/react";
import "./film-view.scss";

export default function FilmView(props: WidgetProps) {
  return (
    <ScrollArea
      className="film-view hidden"
      onClick="film_view_on_click"
      {...props}
    >
      <ScrollAreaContent $ref="content" className="film-view-content" />
      <Scrollbar orientation="horizontal" />
    </ScrollArea>
  );
}
