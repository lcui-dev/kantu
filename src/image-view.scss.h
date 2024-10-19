/** Generated from: image-view.scss */
static const char *css_str_image_view = "\
.image-view text {\
  color: #fff;\
}\
.image-view .percentage {\
  padding: 0 8px;\
  white-space: nowrap;\
}\
.image-view .button {\
  display: flex;\
  align-items: center;\
  justify-content: center;\
  padding: 10px;\
  width: 40px;\
  height: 40px;\
  border-radius: 4px;\
  border: none;\
  background: transparent;\
  flex: 0 0 auto;\
}\
.image-view .button:hover {\
  background: rgba(255, 255, 255, 0.1);\
}\
.image-view .button:active {\
  background: rgba(255, 255, 255, 0.05);\
}\
.image-view .button:disabled,\
.image-view .button:hover:disabled,\
.image-view .button:active:disabled,\
.image-view .button:focus:hover:disabled,\
.image-view .button:focus:active:disabled,\
.image-view .button:focus:hover:active:disabled {\
  background: transparent;\
  opacity: 0.5;\
}\
.image-view .divider {\
  width: 1px;\
  height: 24px;\
  background: rgba(255, 255, 255, 0.1);\
  margin: 0 2px;\
}\
.image-view .switch-button {\
  top: 0;\
  bottom: 56px;\
  width: 100px;\
  padding: 10px;\
  position: absolute;\
  display: flex;\
  align-items: center;\
  opacity: 0;\
}\
.image-view .switch-button:hover {\
  opacity: 1;\
}\
.image-view .switch-button * {\
  width: 20px;\
  height: 50px;\
  line-height: 50px;\
  text-align: center;\
  border-radius: 4px;\
  color: #fff;\
  background: rgb(51, 51, 51);\
}\
.image-view .switch-button.next {\
  right: 0;\
  justify-content: flex-end;\
}\
.image-view .switch-button.prev {\
  left: 0;\
  justify-content: flex-start;\
}\
.image-view .progress {\
  height: 2px;\
}\
.image-view .progress .bar {\
  height: 100%;\
  background: #3b82f6;\
}\
.image-view .tip {\
  opacity: 0.8;\
  display: flex;\
  flex-direction: column;\
}\
.image-view .tip * {\
  color: #fff;\
  text-align: center;\
}\
.image-view .tip .icon {\
  line-height: 1;\
}\
\
.toolbar {\
  flex: none;\
  display: flex;\
  align-items: center;\
  background: rgb(51, 51, 51);\
}\
.toolbar * {\
  flex: 0 0 none;\
}\
.toolbar .icon {\
  font-size: 20px;\
  line-height: 20px;\
}\
.toolbar .button {\
  color: #fff;\
}\
.toolbar .button,\
.toolbar .icon {\
  text-align: center;\
}\
.toolbar .fit-button .icon-fit-fill {\
  display: none;\
}\
.toolbar .fit-button.active .icon-fit {\
  display: none;\
}\
.toolbar .fit-button.active .icon-fit-fill {\
  display: block;\
}\
.toolbar .file-info {\
  flex: 0 0 auto;\
}\
.toolbar .file-info .icon {\
  font-size: 18px;\
  line-height: 18px;\
}\
\
.maximized .toolbar {\
  display: none;\
}\
";
