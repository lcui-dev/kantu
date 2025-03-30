/** Generated from: image-view.scss */
static const char *css_str_image_view = "\
.image-view {\
  display: flex;\
  flex-direction: column;\
  background: #1f1f1f;\
  width: 100%;\
  height: 100%;\
}\
.image-view .content {\
  display: flex;\
  flex: auto;\
  align-items: center;\
  justify-content: center;\
}\
.image-view text {\
  color: #fff;\
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
\
.progress {\
  height: 2px;\
}\
.progress .bar {\
  height: 100%;\
  background: #3b82f6;\
}\
\
.tip {\
  opacity: 0.8;\
  display: flex;\
  flex-direction: column;\
}\
.tip * {\
  color: #fff;\
  text-align: center;\
}\
.tip .icon {\
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
.toolbar .file-info {\
  flex: none;\
  display: flex;\
  margin-right: auto;\
  align-items: center;\
  padding-left: 12px;\
  opacity: 0.5;\
  border-left: 1px solid #fff;\
}\
\
.maximized .toolbar {\
  display: none;\
}\
";
