(() => {
  // ns-hugo:/home/bruno/.cache/hugo_cache/modules/filecache/modules/pkg/mod/github.com/twbs/bootstrap@v5.3.3+incompatible/js/src/dom/data.js
  var elementMap = /* @__PURE__ */ new Map();
  var data_default = {
    set(element, key, instance) {
      if (!elementMap.has(element)) {
        elementMap.set(element, /* @__PURE__ */ new Map());
      }
      const instanceMap = elementMap.get(element);
      if (!instanceMap.has(key) && instanceMap.size !== 0) {
        console.error(`Bootstrap doesn't allow more than one instance per element. Bound instance: ${Array.from(instanceMap.keys())[0]}.`);
        return;
      }
      instanceMap.set(key, instance);
    },
    get(element, key) {
      if (elementMap.has(element)) {
        return elementMap.get(element).get(key) || null;
      }
      return null;
    },
    remove(element, key) {
      if (!elementMap.has(element)) {
        return;
      }
      const instanceMap = elementMap.get(element);
      instanceMap.delete(key);
      if (instanceMap.size === 0) {
        elementMap.delete(element);
      }
    }
  };

  // ns-hugo:/home/bruno/.cache/hugo_cache/modules/filecache/modules/pkg/mod/github.com/twbs/bootstrap@v5.3.3+incompatible/js/src/util/index.js
  var MILLISECONDS_MULTIPLIER = 1e3;
  var TRANSITION_END = "transitionend";
  var parseSelector = (selector) => {
    if (selector && window.CSS && window.CSS.escape) {
      selector = selector.replace(/#([^\s"#']+)/g, (match, id) => `#${CSS.escape(id)}`);
    }
    return selector;
  };
  var toType = (object) => {
    if (object === null || object === void 0) {
      return `${object}`;
    }
    return Object.prototype.toString.call(object).match(/\s([a-z]+)/i)[1].toLowerCase();
  };
  var getTransitionDurationFromElement = (element) => {
    if (!element) {
      return 0;
    }
    let { transitionDuration, transitionDelay } = window.getComputedStyle(element);
    const floatTransitionDuration = Number.parseFloat(transitionDuration);
    const floatTransitionDelay = Number.parseFloat(transitionDelay);
    if (!floatTransitionDuration && !floatTransitionDelay) {
      return 0;
    }
    transitionDuration = transitionDuration.split(",")[0];
    transitionDelay = transitionDelay.split(",")[0];
    return (Number.parseFloat(transitionDuration) + Number.parseFloat(transitionDelay)) * MILLISECONDS_MULTIPLIER;
  };
  var triggerTransitionEnd = (element) => {
    element.dispatchEvent(new Event(TRANSITION_END));
  };
  var isElement = (object) => {
    if (!object || typeof object !== "object") {
      return false;
    }
    if (typeof object.jquery !== "undefined") {
      object = object[0];
    }
    return typeof object.nodeType !== "undefined";
  };
  var getElement = (object) => {
    if (isElement(object)) {
      return object.jquery ? object[0] : object;
    }
    if (typeof object === "string" && object.length > 0) {
      return document.querySelector(parseSelector(object));
    }
    return null;
  };
  var isVisible = (element) => {
    if (!isElement(element) || element.getClientRects().length === 0) {
      return false;
    }
    const elementIsVisible = getComputedStyle(element).getPropertyValue("visibility") === "visible";
    const closedDetails = element.closest("details:not([open])");
    if (!closedDetails) {
      return elementIsVisible;
    }
    if (closedDetails !== element) {
      const summary = element.closest("summary");
      if (summary && summary.parentNode !== closedDetails) {
        return false;
      }
      if (summary === null) {
        return false;
      }
    }
    return elementIsVisible;
  };
  var isDisabled = (element) => {
    if (!element || element.nodeType !== Node.ELEMENT_NODE) {
      return true;
    }
    if (element.classList.contains("disabled")) {
      return true;
    }
    if (typeof element.disabled !== "undefined") {
      return element.disabled;
    }
    return element.hasAttribute("disabled") && element.getAttribute("disabled") !== "false";
  };
  var getjQuery = () => {
    if (window.jQuery && !document.body.hasAttribute("data-bs-no-jquery")) {
      return window.jQuery;
    }
    return null;
  };
  var DOMContentLoadedCallbacks = [];
  var onDOMContentLoaded = (callback) => {
    if (document.readyState === "loading") {
      if (!DOMContentLoadedCallbacks.length) {
        document.addEventListener("DOMContentLoaded", () => {
          for (const callback2 of DOMContentLoadedCallbacks) {
            callback2();
          }
        });
      }
      DOMContentLoadedCallbacks.push(callback);
    } else {
      callback();
    }
  };
  var defineJQueryPlugin = (plugin) => {
    onDOMContentLoaded(() => {
      const $ = getjQuery();
      if ($) {
        const name = plugin.NAME;
        const JQUERY_NO_CONFLICT = $.fn[name];
        $.fn[name] = plugin.jQueryInterface;
        $.fn[name].Constructor = plugin;
        $.fn[name].noConflict = () => {
          $.fn[name] = JQUERY_NO_CONFLICT;
          return plugin.jQueryInterface;
        };
      }
    });
  };
  var execute = (possibleCallback, args = [], defaultValue = possibleCallback) => {
    return typeof possibleCallback === "function" ? possibleCallback(...args) : defaultValue;
  };
  var executeAfterTransition = (callback, transitionElement, waitForTransition = true) => {
    if (!waitForTransition) {
      execute(callback);
      return;
    }
    const durationPadding = 5;
    const emulatedDuration = getTransitionDurationFromElement(transitionElement) + durationPadding;
    let called = false;
    const handler = ({ target }) => {
      if (target !== transitionElement) {
        return;
      }
      called = true;
      transitionElement.removeEventListener(TRANSITION_END, handler);
      execute(callback);
    };
    transitionElement.addEventListener(TRANSITION_END, handler);
    setTimeout(() => {
      if (!called) {
        triggerTransitionEnd(transitionElement);
      }
    }, emulatedDuration);
  };
  var getNextActiveElement = (list, activeElement, shouldGetNext, isCycleAllowed) => {
    const listLength = list.length;
    let index = list.indexOf(activeElement);
    if (index === -1) {
      return !shouldGetNext && isCycleAllowed ? list[listLength - 1] : list[0];
    }
    index += shouldGetNext ? 1 : -1;
    if (isCycleAllowed) {
      index = (index + listLength) % listLength;
    }
    return list[Math.max(0, Math.min(index, listLength - 1))];
  };

  // ns-hugo:/home/bruno/.cache/hugo_cache/modules/filecache/modules/pkg/mod/github.com/twbs/bootstrap@v5.3.3+incompatible/js/src/dom/event-handler.js
  var namespaceRegex = /[^.]*(?=\..*)\.|.*/;
  var stripNameRegex = /\..*/;
  var stripUidRegex = /::\d+$/;
  var eventRegistry = {};
  var uidEvent = 1;
  var customEvents = {
    mouseenter: "mouseover",
    mouseleave: "mouseout"
  };
  var nativeEvents = /* @__PURE__ */ new Set([
    "click",
    "dblclick",
    "mouseup",
    "mousedown",
    "contextmenu",
    "mousewheel",
    "DOMMouseScroll",
    "mouseover",
    "mouseout",
    "mousemove",
    "selectstart",
    "selectend",
    "keydown",
    "keypress",
    "keyup",
    "orientationchange",
    "touchstart",
    "touchmove",
    "touchend",
    "touchcancel",
    "pointerdown",
    "pointermove",
    "pointerup",
    "pointerleave",
    "pointercancel",
    "gesturestart",
    "gesturechange",
    "gestureend",
    "focus",
    "blur",
    "change",
    "reset",
    "select",
    "submit",
    "focusin",
    "focusout",
    "load",
    "unload",
    "beforeunload",
    "resize",
    "move",
    "DOMContentLoaded",
    "readystatechange",
    "error",
    "abort",
    "scroll"
  ]);
  function makeEventUid(element, uid) {
    return uid && `${uid}::${uidEvent++}` || element.uidEvent || uidEvent++;
  }
  function getElementEvents(element) {
    const uid = makeEventUid(element);
    element.uidEvent = uid;
    eventRegistry[uid] = eventRegistry[uid] || {};
    return eventRegistry[uid];
  }
  function bootstrapHandler(element, fn) {
    return function handler(event) {
      hydrateObj(event, { delegateTarget: element });
      if (handler.oneOff) {
        EventHandler.off(element, event.type, fn);
      }
      return fn.apply(element, [event]);
    };
  }
  function bootstrapDelegationHandler(element, selector, fn) {
    return function handler(event) {
      const domElements = element.querySelectorAll(selector);
      for (let { target } = event; target && target !== this; target = target.parentNode) {
        for (const domElement of domElements) {
          if (domElement !== target) {
            continue;
          }
          hydrateObj(event, { delegateTarget: target });
          if (handler.oneOff) {
            EventHandler.off(element, event.type, selector, fn);
          }
          return fn.apply(target, [event]);
        }
      }
    };
  }
  function findHandler(events, callable, delegationSelector = null) {
    return Object.values(events).find((event) => event.callable === callable && event.delegationSelector === delegationSelector);
  }
  function normalizeParameters(originalTypeEvent, handler, delegationFunction) {
    const isDelegated = typeof handler === "string";
    const callable = isDelegated ? delegationFunction : handler || delegationFunction;
    let typeEvent = getTypeEvent(originalTypeEvent);
    if (!nativeEvents.has(typeEvent)) {
      typeEvent = originalTypeEvent;
    }
    return [isDelegated, callable, typeEvent];
  }
  function addHandler(element, originalTypeEvent, handler, delegationFunction, oneOff) {
    if (typeof originalTypeEvent !== "string" || !element) {
      return;
    }
    let [isDelegated, callable, typeEvent] = normalizeParameters(originalTypeEvent, handler, delegationFunction);
    if (originalTypeEvent in customEvents) {
      const wrapFunction = (fn2) => {
        return function(event) {
          if (!event.relatedTarget || event.relatedTarget !== event.delegateTarget && !event.delegateTarget.contains(event.relatedTarget)) {
            return fn2.call(this, event);
          }
        };
      };
      callable = wrapFunction(callable);
    }
    const events = getElementEvents(element);
    const handlers = events[typeEvent] || (events[typeEvent] = {});
    const previousFunction = findHandler(handlers, callable, isDelegated ? handler : null);
    if (previousFunction) {
      previousFunction.oneOff = previousFunction.oneOff && oneOff;
      return;
    }
    const uid = makeEventUid(callable, originalTypeEvent.replace(namespaceRegex, ""));
    const fn = isDelegated ? bootstrapDelegationHandler(element, handler, callable) : bootstrapHandler(element, callable);
    fn.delegationSelector = isDelegated ? handler : null;
    fn.callable = callable;
    fn.oneOff = oneOff;
    fn.uidEvent = uid;
    handlers[uid] = fn;
    element.addEventListener(typeEvent, fn, isDelegated);
  }
  function removeHandler(element, events, typeEvent, handler, delegationSelector) {
    const fn = findHandler(events[typeEvent], handler, delegationSelector);
    if (!fn) {
      return;
    }
    element.removeEventListener(typeEvent, fn, Boolean(delegationSelector));
    delete events[typeEvent][fn.uidEvent];
  }
  function removeNamespacedHandlers(element, events, typeEvent, namespace) {
    const storeElementEvent = events[typeEvent] || {};
    for (const [handlerKey, event] of Object.entries(storeElementEvent)) {
      if (handlerKey.includes(namespace)) {
        removeHandler(element, events, typeEvent, event.callable, event.delegationSelector);
      }
    }
  }
  function getTypeEvent(event) {
    event = event.replace(stripNameRegex, "");
    return customEvents[event] || event;
  }
  var EventHandler = {
    on(element, event, handler, delegationFunction) {
      addHandler(element, event, handler, delegationFunction, false);
    },
    one(element, event, handler, delegationFunction) {
      addHandler(element, event, handler, delegationFunction, true);
    },
    off(element, originalTypeEvent, handler, delegationFunction) {
      if (typeof originalTypeEvent !== "string" || !element) {
        return;
      }
      const [isDelegated, callable, typeEvent] = normalizeParameters(originalTypeEvent, handler, delegationFunction);
      const inNamespace = typeEvent !== originalTypeEvent;
      const events = getElementEvents(element);
      const storeElementEvent = events[typeEvent] || {};
      const isNamespace = originalTypeEvent.startsWith(".");
      if (typeof callable !== "undefined") {
        if (!Object.keys(storeElementEvent).length) {
          return;
        }
        removeHandler(element, events, typeEvent, callable, isDelegated ? handler : null);
        return;
      }
      if (isNamespace) {
        for (const elementEvent of Object.keys(events)) {
          removeNamespacedHandlers(element, events, elementEvent, originalTypeEvent.slice(1));
        }
      }
      for (const [keyHandlers, event] of Object.entries(storeElementEvent)) {
        const handlerKey = keyHandlers.replace(stripUidRegex, "");
        if (!inNamespace || originalTypeEvent.includes(handlerKey)) {
          removeHandler(element, events, typeEvent, event.callable, event.delegationSelector);
        }
      }
    },
    trigger(element, event, args) {
      if (typeof event !== "string" || !element) {
        return null;
      }
      const $ = getjQuery();
      const typeEvent = getTypeEvent(event);
      const inNamespace = event !== typeEvent;
      let jQueryEvent = null;
      let bubbles = true;
      let nativeDispatch = true;
      let defaultPrevented = false;
      if (inNamespace && $) {
        jQueryEvent = $.Event(event, args);
        $(element).trigger(jQueryEvent);
        bubbles = !jQueryEvent.isPropagationStopped();
        nativeDispatch = !jQueryEvent.isImmediatePropagationStopped();
        defaultPrevented = jQueryEvent.isDefaultPrevented();
      }
      const evt = hydrateObj(new Event(event, { bubbles, cancelable: true }), args);
      if (defaultPrevented) {
        evt.preventDefault();
      }
      if (nativeDispatch) {
        element.dispatchEvent(evt);
      }
      if (evt.defaultPrevented && jQueryEvent) {
        jQueryEvent.preventDefault();
      }
      return evt;
    }
  };
  function hydrateObj(obj, meta = {}) {
    for (const [key, value] of Object.entries(meta)) {
      try {
        obj[key] = value;
      } catch (e) {
        Object.defineProperty(obj, key, {
          configurable: true,
          get() {
            return value;
          }
        });
      }
    }
    return obj;
  }
  var event_handler_default = EventHandler;

  // ns-hugo:/home/bruno/.cache/hugo_cache/modules/filecache/modules/pkg/mod/github.com/twbs/bootstrap@v5.3.3+incompatible/js/src/dom/manipulator.js
  function normalizeData(value) {
    if (value === "true") {
      return true;
    }
    if (value === "false") {
      return false;
    }
    if (value === Number(value).toString()) {
      return Number(value);
    }
    if (value === "" || value === "null") {
      return null;
    }
    if (typeof value !== "string") {
      return value;
    }
    try {
      return JSON.parse(decodeURIComponent(value));
    } catch (e) {
      return value;
    }
  }
  function normalizeDataKey(key) {
    return key.replace(/[A-Z]/g, (chr) => `-${chr.toLowerCase()}`);
  }
  var Manipulator = {
    setDataAttribute(element, key, value) {
      element.setAttribute(`data-bs-${normalizeDataKey(key)}`, value);
    },
    removeDataAttribute(element, key) {
      element.removeAttribute(`data-bs-${normalizeDataKey(key)}`);
    },
    getDataAttributes(element) {
      if (!element) {
        return {};
      }
      const attributes = {};
      const bsKeys = Object.keys(element.dataset).filter((key) => key.startsWith("bs") && !key.startsWith("bsConfig"));
      for (const key of bsKeys) {
        let pureKey = key.replace(/^bs/, "");
        pureKey = pureKey.charAt(0).toLowerCase() + pureKey.slice(1, pureKey.length);
        attributes[pureKey] = normalizeData(element.dataset[key]);
      }
      return attributes;
    },
    getDataAttribute(element, key) {
      return normalizeData(element.getAttribute(`data-bs-${normalizeDataKey(key)}`));
    }
  };
  var manipulator_default = Manipulator;

  // ns-hugo:/home/bruno/.cache/hugo_cache/modules/filecache/modules/pkg/mod/github.com/twbs/bootstrap@v5.3.3+incompatible/js/src/util/config.js
  var Config = class {
    // Getters
    static get Default() {
      return {};
    }
    static get DefaultType() {
      return {};
    }
    static get NAME() {
      throw new Error('You have to implement the static method "NAME", for each component!');
    }
    _getConfig(config) {
      config = this._mergeConfigObj(config);
      config = this._configAfterMerge(config);
      this._typeCheckConfig(config);
      return config;
    }
    _configAfterMerge(config) {
      return config;
    }
    _mergeConfigObj(config, element) {
      const jsonConfig = isElement(element) ? manipulator_default.getDataAttribute(element, "config") : {};
      return {
        ...this.constructor.Default,
        ...typeof jsonConfig === "object" ? jsonConfig : {},
        ...isElement(element) ? manipulator_default.getDataAttributes(element) : {},
        ...typeof config === "object" ? config : {}
      };
    }
    _typeCheckConfig(config, configTypes = this.constructor.DefaultType) {
      for (const [property, expectedTypes] of Object.entries(configTypes)) {
        const value = config[property];
        const valueType = isElement(value) ? "element" : toType(value);
        if (!new RegExp(expectedTypes).test(valueType)) {
          throw new TypeError(
            `${this.constructor.NAME.toUpperCase()}: Option "${property}" provided type "${valueType}" but expected type "${expectedTypes}".`
          );
        }
      }
    }
  };
  var config_default = Config;

  // ns-hugo:/home/bruno/.cache/hugo_cache/modules/filecache/modules/pkg/mod/github.com/twbs/bootstrap@v5.3.3+incompatible/js/src/base-component.js
  var VERSION = "5.3.3";
  var BaseComponent = class extends config_default {
    constructor(element, config) {
      super();
      element = getElement(element);
      if (!element) {
        return;
      }
      this._element = element;
      this._config = this._getConfig(config);
      data_default.set(this._element, this.constructor.DATA_KEY, this);
    }
    // Public
    dispose() {
      data_default.remove(this._element, this.constructor.DATA_KEY);
      event_handler_default.off(this._element, this.constructor.EVENT_KEY);
      for (const propertyName of Object.getOwnPropertyNames(this)) {
        this[propertyName] = null;
      }
    }
    _queueCallback(callback, element, isAnimated = true) {
      executeAfterTransition(callback, element, isAnimated);
    }
    _getConfig(config) {
      config = this._mergeConfigObj(config, this._element);
      config = this._configAfterMerge(config);
      this._typeCheckConfig(config);
      return config;
    }
    // Static
    static getInstance(element) {
      return data_default.get(getElement(element), this.DATA_KEY);
    }
    static getOrCreateInstance(element, config = {}) {
      return this.getInstance(element) || new this(element, typeof config === "object" ? config : null);
    }
    static get VERSION() {
      return VERSION;
    }
    static get DATA_KEY() {
      return `bs.${this.NAME}`;
    }
    static get EVENT_KEY() {
      return `.${this.DATA_KEY}`;
    }
    static eventName(name) {
      return `${name}${this.EVENT_KEY}`;
    }
  };
  var base_component_default = BaseComponent;

  // ns-hugo:/home/bruno/.cache/hugo_cache/modules/filecache/modules/pkg/mod/github.com/twbs/bootstrap@v5.3.3+incompatible/js/src/dom/selector-engine.js
  var getSelector = (element) => {
    let selector = element.getAttribute("data-bs-target");
    if (!selector || selector === "#") {
      let hrefAttribute = element.getAttribute("href");
      if (!hrefAttribute || !hrefAttribute.includes("#") && !hrefAttribute.startsWith(".")) {
        return null;
      }
      if (hrefAttribute.includes("#") && !hrefAttribute.startsWith("#")) {
        hrefAttribute = `#${hrefAttribute.split("#")[1]}`;
      }
      selector = hrefAttribute && hrefAttribute !== "#" ? hrefAttribute.trim() : null;
    }
    return selector ? selector.split(",").map((sel) => parseSelector(sel)).join(",") : null;
  };
  var SelectorEngine = {
    find(selector, element = document.documentElement) {
      return [].concat(...Element.prototype.querySelectorAll.call(element, selector));
    },
    findOne(selector, element = document.documentElement) {
      return Element.prototype.querySelector.call(element, selector);
    },
    children(element, selector) {
      return [].concat(...element.children).filter((child) => child.matches(selector));
    },
    parents(element, selector) {
      const parents = [];
      let ancestor = element.parentNode.closest(selector);
      while (ancestor) {
        parents.push(ancestor);
        ancestor = ancestor.parentNode.closest(selector);
      }
      return parents;
    },
    prev(element, selector) {
      let previous = element.previousElementSibling;
      while (previous) {
        if (previous.matches(selector)) {
          return [previous];
        }
        previous = previous.previousElementSibling;
      }
      return [];
    },
    // TODO: this is now unused; remove later along with prev()
    next(element, selector) {
      let next = element.nextElementSibling;
      while (next) {
        if (next.matches(selector)) {
          return [next];
        }
        next = next.nextElementSibling;
      }
      return [];
    },
    focusableChildren(element) {
      const focusables = [
        "a",
        "button",
        "input",
        "textarea",
        "select",
        "details",
        "[tabindex]",
        '[contenteditable="true"]'
      ].map((selector) => `${selector}:not([tabindex^="-"])`).join(",");
      return this.find(focusables, element).filter((el) => !isDisabled(el) && isVisible(el));
    },
    getSelectorFromElement(element) {
      const selector = getSelector(element);
      if (selector) {
        return SelectorEngine.findOne(selector) ? selector : null;
      }
      return null;
    },
    getElementFromSelector(element) {
      const selector = getSelector(element);
      return selector ? SelectorEngine.findOne(selector) : null;
    },
    getMultipleElementsFromSelector(element) {
      const selector = getSelector(element);
      return selector ? SelectorEngine.find(selector) : [];
    }
  };
  var selector_engine_default = SelectorEngine;

  // ns-hugo:/home/bruno/.cache/hugo_cache/modules/filecache/modules/pkg/mod/github.com/twbs/bootstrap@v5.3.3+incompatible/js/src/tab.js
  var NAME = "tab";
  var DATA_KEY = "bs.tab";
  var EVENT_KEY = `.${DATA_KEY}`;
  var EVENT_HIDE = `hide${EVENT_KEY}`;
  var EVENT_HIDDEN = `hidden${EVENT_KEY}`;
  var EVENT_SHOW = `show${EVENT_KEY}`;
  var EVENT_SHOWN = `shown${EVENT_KEY}`;
  var EVENT_CLICK_DATA_API = `click${EVENT_KEY}`;
  var EVENT_KEYDOWN = `keydown${EVENT_KEY}`;
  var EVENT_LOAD_DATA_API = `load${EVENT_KEY}`;
  var ARROW_LEFT_KEY = "ArrowLeft";
  var ARROW_RIGHT_KEY = "ArrowRight";
  var ARROW_UP_KEY = "ArrowUp";
  var ARROW_DOWN_KEY = "ArrowDown";
  var HOME_KEY = "Home";
  var END_KEY = "End";
  var CLASS_NAME_ACTIVE = "active";
  var CLASS_NAME_FADE = "fade";
  var CLASS_NAME_SHOW = "show";
  var CLASS_DROPDOWN = "dropdown";
  var SELECTOR_DROPDOWN_TOGGLE = ".dropdown-toggle";
  var SELECTOR_DROPDOWN_MENU = ".dropdown-menu";
  var NOT_SELECTOR_DROPDOWN_TOGGLE = `:not(${SELECTOR_DROPDOWN_TOGGLE})`;
  var SELECTOR_TAB_PANEL = '.list-group, .nav, [role="tablist"]';
  var SELECTOR_OUTER = ".nav-item, .list-group-item";
  var SELECTOR_INNER = `.nav-link${NOT_SELECTOR_DROPDOWN_TOGGLE}, .list-group-item${NOT_SELECTOR_DROPDOWN_TOGGLE}, [role="tab"]${NOT_SELECTOR_DROPDOWN_TOGGLE}`;
  var SELECTOR_DATA_TOGGLE = '[data-bs-toggle="tab"], [data-bs-toggle="pill"], [data-bs-toggle="list"]';
  var SELECTOR_INNER_ELEM = `${SELECTOR_INNER}, ${SELECTOR_DATA_TOGGLE}`;
  var SELECTOR_DATA_TOGGLE_ACTIVE = `.${CLASS_NAME_ACTIVE}[data-bs-toggle="tab"], .${CLASS_NAME_ACTIVE}[data-bs-toggle="pill"], .${CLASS_NAME_ACTIVE}[data-bs-toggle="list"]`;
  var Tab = class _Tab extends base_component_default {
    constructor(element) {
      super(element);
      this._parent = this._element.closest(SELECTOR_TAB_PANEL);
      if (!this._parent) {
        return;
      }
      this._setInitialAttributes(this._parent, this._getChildren());
      event_handler_default.on(this._element, EVENT_KEYDOWN, (event) => this._keydown(event));
    }
    // Getters
    static get NAME() {
      return NAME;
    }
    // Public
    show() {
      const innerElem = this._element;
      if (this._elemIsActive(innerElem)) {
        return;
      }
      const active = this._getActiveElem();
      const hideEvent = active ? event_handler_default.trigger(active, EVENT_HIDE, { relatedTarget: innerElem }) : null;
      const showEvent = event_handler_default.trigger(innerElem, EVENT_SHOW, { relatedTarget: active });
      if (showEvent.defaultPrevented || hideEvent && hideEvent.defaultPrevented) {
        return;
      }
      this._deactivate(active, innerElem);
      this._activate(innerElem, active);
    }
    // Private
    _activate(element, relatedElem) {
      if (!element) {
        return;
      }
      element.classList.add(CLASS_NAME_ACTIVE);
      this._activate(selector_engine_default.getElementFromSelector(element));
      const complete = () => {
        if (element.getAttribute("role") !== "tab") {
          element.classList.add(CLASS_NAME_SHOW);
          return;
        }
        element.removeAttribute("tabindex");
        element.setAttribute("aria-selected", true);
        this._toggleDropDown(element, true);
        event_handler_default.trigger(element, EVENT_SHOWN, {
          relatedTarget: relatedElem
        });
      };
      this._queueCallback(complete, element, element.classList.contains(CLASS_NAME_FADE));
    }
    _deactivate(element, relatedElem) {
      if (!element) {
        return;
      }
      element.classList.remove(CLASS_NAME_ACTIVE);
      element.blur();
      this._deactivate(selector_engine_default.getElementFromSelector(element));
      const complete = () => {
        if (element.getAttribute("role") !== "tab") {
          element.classList.remove(CLASS_NAME_SHOW);
          return;
        }
        element.setAttribute("aria-selected", false);
        element.setAttribute("tabindex", "-1");
        this._toggleDropDown(element, false);
        event_handler_default.trigger(element, EVENT_HIDDEN, { relatedTarget: relatedElem });
      };
      this._queueCallback(complete, element, element.classList.contains(CLASS_NAME_FADE));
    }
    _keydown(event) {
      if (![ARROW_LEFT_KEY, ARROW_RIGHT_KEY, ARROW_UP_KEY, ARROW_DOWN_KEY, HOME_KEY, END_KEY].includes(event.key)) {
        return;
      }
      event.stopPropagation();
      event.preventDefault();
      const children = this._getChildren().filter((element) => !isDisabled(element));
      let nextActiveElement;
      if ([HOME_KEY, END_KEY].includes(event.key)) {
        nextActiveElement = children[event.key === HOME_KEY ? 0 : children.length - 1];
      } else {
        const isNext = [ARROW_RIGHT_KEY, ARROW_DOWN_KEY].includes(event.key);
        nextActiveElement = getNextActiveElement(children, event.target, isNext, true);
      }
      if (nextActiveElement) {
        nextActiveElement.focus({ preventScroll: true });
        _Tab.getOrCreateInstance(nextActiveElement).show();
      }
    }
    _getChildren() {
      return selector_engine_default.find(SELECTOR_INNER_ELEM, this._parent);
    }
    _getActiveElem() {
      return this._getChildren().find((child) => this._elemIsActive(child)) || null;
    }
    _setInitialAttributes(parent, children) {
      this._setAttributeIfNotExists(parent, "role", "tablist");
      for (const child of children) {
        this._setInitialAttributesOnChild(child);
      }
    }
    _setInitialAttributesOnChild(child) {
      child = this._getInnerElement(child);
      const isActive = this._elemIsActive(child);
      const outerElem = this._getOuterElement(child);
      child.setAttribute("aria-selected", isActive);
      if (outerElem !== child) {
        this._setAttributeIfNotExists(outerElem, "role", "presentation");
      }
      if (!isActive) {
        child.setAttribute("tabindex", "-1");
      }
      this._setAttributeIfNotExists(child, "role", "tab");
      this._setInitialAttributesOnTargetPanel(child);
    }
    _setInitialAttributesOnTargetPanel(child) {
      const target = selector_engine_default.getElementFromSelector(child);
      if (!target) {
        return;
      }
      this._setAttributeIfNotExists(target, "role", "tabpanel");
      if (child.id) {
        this._setAttributeIfNotExists(target, "aria-labelledby", `${child.id}`);
      }
    }
    _toggleDropDown(element, open) {
      const outerElem = this._getOuterElement(element);
      if (!outerElem.classList.contains(CLASS_DROPDOWN)) {
        return;
      }
      const toggle = (selector, className) => {
        const element2 = selector_engine_default.findOne(selector, outerElem);
        if (element2) {
          element2.classList.toggle(className, open);
        }
      };
      toggle(SELECTOR_DROPDOWN_TOGGLE, CLASS_NAME_ACTIVE);
      toggle(SELECTOR_DROPDOWN_MENU, CLASS_NAME_SHOW);
      outerElem.setAttribute("aria-expanded", open);
    }
    _setAttributeIfNotExists(element, attribute, value) {
      if (!element.hasAttribute(attribute)) {
        element.setAttribute(attribute, value);
      }
    }
    _elemIsActive(elem) {
      return elem.classList.contains(CLASS_NAME_ACTIVE);
    }
    // Try to get the inner element (usually the .nav-link)
    _getInnerElement(elem) {
      return elem.matches(SELECTOR_INNER_ELEM) ? elem : selector_engine_default.findOne(SELECTOR_INNER_ELEM, elem);
    }
    // Try to get the outer element (usually the .nav-item)
    _getOuterElement(elem) {
      return elem.closest(SELECTOR_OUTER) || elem;
    }
    // Static
    static jQueryInterface(config) {
      return this.each(function() {
        const data = _Tab.getOrCreateInstance(this);
        if (typeof config !== "string") {
          return;
        }
        if (data[config] === void 0 || config.startsWith("_") || config === "constructor") {
          throw new TypeError(`No method named "${config}"`);
        }
        data[config]();
      });
    }
  };
  event_handler_default.on(document, EVENT_CLICK_DATA_API, SELECTOR_DATA_TOGGLE, function(event) {
    if (["A", "AREA"].includes(this.tagName)) {
      event.preventDefault();
    }
    if (isDisabled(this)) {
      return;
    }
    Tab.getOrCreateInstance(this).show();
  });
  event_handler_default.on(window, EVENT_LOAD_DATA_API, () => {
    for (const element of selector_engine_default.find(SELECTOR_DATA_TOGGLE_ACTIVE)) {
      Tab.getOrCreateInstance(element);
    }
  });
  defineJQueryPlugin(Tab);
  var tab_default = Tab;

  // <stdin>
  var stdin_default = {
    Tab: tab_default
  };
})();
//# sourceMappingURL=data:application/json;base64,ewogICJ2ZXJzaW9uIjogMywKICAic291cmNlcyI6IFsiL2hvbWUvYnJ1bm8vLmNhY2hlL2h1Z29fY2FjaGUvbW9kdWxlcy9maWxlY2FjaGUvbW9kdWxlcy9wa2cvbW9kL2dpdGh1Yi5jb20vdHdicy9ib290c3RyYXBAdjUuMy4zK2luY29tcGF0aWJsZS9qcy9zcmMvZG9tL2RhdGEuanMiLCAiL2hvbWUvYnJ1bm8vLmNhY2hlL2h1Z29fY2FjaGUvbW9kdWxlcy9maWxlY2FjaGUvbW9kdWxlcy9wa2cvbW9kL2dpdGh1Yi5jb20vdHdicy9ib290c3RyYXBAdjUuMy4zK2luY29tcGF0aWJsZS9qcy9zcmMvdXRpbC9pbmRleC5qcyIsICIvaG9tZS9icnVuby8uY2FjaGUvaHVnb19jYWNoZS9tb2R1bGVzL2ZpbGVjYWNoZS9tb2R1bGVzL3BrZy9tb2QvZ2l0aHViLmNvbS90d2JzL2Jvb3RzdHJhcEB2NS4zLjMraW5jb21wYXRpYmxlL2pzL3NyYy9kb20vZXZlbnQtaGFuZGxlci5qcyIsICIvaG9tZS9icnVuby8uY2FjaGUvaHVnb19jYWNoZS9tb2R1bGVzL2ZpbGVjYWNoZS9tb2R1bGVzL3BrZy9tb2QvZ2l0aHViLmNvbS90d2JzL2Jvb3RzdHJhcEB2NS4zLjMraW5jb21wYXRpYmxlL2pzL3NyYy9kb20vbWFuaXB1bGF0b3IuanMiLCAiL2hvbWUvYnJ1bm8vLmNhY2hlL2h1Z29fY2FjaGUvbW9kdWxlcy9maWxlY2FjaGUvbW9kdWxlcy9wa2cvbW9kL2dpdGh1Yi5jb20vdHdicy9ib290c3RyYXBAdjUuMy4zK2luY29tcGF0aWJsZS9qcy9zcmMvdXRpbC9jb25maWcuanMiLCAiL2hvbWUvYnJ1bm8vLmNhY2hlL2h1Z29fY2FjaGUvbW9kdWxlcy9maWxlY2FjaGUvbW9kdWxlcy9wa2cvbW9kL2dpdGh1Yi5jb20vdHdicy9ib290c3RyYXBAdjUuMy4zK2luY29tcGF0aWJsZS9qcy9zcmMvYmFzZS1jb21wb25lbnQuanMiLCAiL2hvbWUvYnJ1bm8vLmNhY2hlL2h1Z29fY2FjaGUvbW9kdWxlcy9maWxlY2FjaGUvbW9kdWxlcy9wa2cvbW9kL2dpdGh1Yi5jb20vdHdicy9ib290c3RyYXBAdjUuMy4zK2luY29tcGF0aWJsZS9qcy9zcmMvZG9tL3NlbGVjdG9yLWVuZ2luZS5qcyIsICIvaG9tZS9icnVuby8uY2FjaGUvaHVnb19jYWNoZS9tb2R1bGVzL2ZpbGVjYWNoZS9tb2R1bGVzL3BrZy9tb2QvZ2l0aHViLmNvbS90d2JzL2Jvb3RzdHJhcEB2NS4zLjMraW5jb21wYXRpYmxlL2pzL3NyYy90YWIuanMiLCAiPHN0ZGluPiJdLAogICJzb3VyY2VzQ29udGVudCI6IFsiLyoqXG4gKiAtLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLVxuICogQm9vdHN0cmFwIGRvbS9kYXRhLmpzXG4gKiBMaWNlbnNlZCB1bmRlciBNSVQgKGh0dHBzOi8vZ2l0aHViLmNvbS90d2JzL2Jvb3RzdHJhcC9ibG9iL21haW4vTElDRU5TRSlcbiAqIC0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tXG4gKi9cblxuLyoqXG4gKiBDb25zdGFudHNcbiAqL1xuXG5jb25zdCBlbGVtZW50TWFwID0gbmV3IE1hcCgpXG5cbmV4cG9ydCBkZWZhdWx0IHtcbiAgc2V0KGVsZW1lbnQsIGtleSwgaW5zdGFuY2UpIHtcbiAgICBpZiAoIWVsZW1lbnRNYXAuaGFzKGVsZW1lbnQpKSB7XG4gICAgICBlbGVtZW50TWFwLnNldChlbGVtZW50LCBuZXcgTWFwKCkpXG4gICAgfVxuXG4gICAgY29uc3QgaW5zdGFuY2VNYXAgPSBlbGVtZW50TWFwLmdldChlbGVtZW50KVxuXG4gICAgLy8gbWFrZSBpdCBjbGVhciB3ZSBvbmx5IHdhbnQgb25lIGluc3RhbmNlIHBlciBlbGVtZW50XG4gICAgLy8gY2FuIGJlIHJlbW92ZWQgbGF0ZXIgd2hlbiBtdWx0aXBsZSBrZXkvaW5zdGFuY2VzIGFyZSBmaW5lIHRvIGJlIHVzZWRcbiAgICBpZiAoIWluc3RhbmNlTWFwLmhhcyhrZXkpICYmIGluc3RhbmNlTWFwLnNpemUgIT09IDApIHtcbiAgICAgIC8vIGVzbGludC1kaXNhYmxlLW5leHQtbGluZSBuby1jb25zb2xlXG4gICAgICBjb25zb2xlLmVycm9yKGBCb290c3RyYXAgZG9lc24ndCBhbGxvdyBtb3JlIHRoYW4gb25lIGluc3RhbmNlIHBlciBlbGVtZW50LiBCb3VuZCBpbnN0YW5jZTogJHtBcnJheS5mcm9tKGluc3RhbmNlTWFwLmtleXMoKSlbMF19LmApXG4gICAgICByZXR1cm5cbiAgICB9XG5cbiAgICBpbnN0YW5jZU1hcC5zZXQoa2V5LCBpbnN0YW5jZSlcbiAgfSxcblxuICBnZXQoZWxlbWVudCwga2V5KSB7XG4gICAgaWYgKGVsZW1lbnRNYXAuaGFzKGVsZW1lbnQpKSB7XG4gICAgICByZXR1cm4gZWxlbWVudE1hcC5nZXQoZWxlbWVudCkuZ2V0KGtleSkgfHwgbnVsbFxuICAgIH1cblxuICAgIHJldHVybiBudWxsXG4gIH0sXG5cbiAgcmVtb3ZlKGVsZW1lbnQsIGtleSkge1xuICAgIGlmICghZWxlbWVudE1hcC5oYXMoZWxlbWVudCkpIHtcbiAgICAgIHJldHVyblxuICAgIH1cblxuICAgIGNvbnN0IGluc3RhbmNlTWFwID0gZWxlbWVudE1hcC5nZXQoZWxlbWVudClcblxuICAgIGluc3RhbmNlTWFwLmRlbGV0ZShrZXkpXG5cbiAgICAvLyBmcmVlIHVwIGVsZW1lbnQgcmVmZXJlbmNlcyBpZiB0aGVyZSBhcmUgbm8gaW5zdGFuY2VzIGxlZnQgZm9yIGFuIGVsZW1lbnRcbiAgICBpZiAoaW5zdGFuY2VNYXAuc2l6ZSA9PT0gMCkge1xuICAgICAgZWxlbWVudE1hcC5kZWxldGUoZWxlbWVudClcbiAgICB9XG4gIH1cbn1cbiIsICIvKipcbiAqIC0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tXG4gKiBCb290c3RyYXAgdXRpbC9pbmRleC5qc1xuICogTGljZW5zZWQgdW5kZXIgTUlUIChodHRwczovL2dpdGh1Yi5jb20vdHdicy9ib290c3RyYXAvYmxvYi9tYWluL0xJQ0VOU0UpXG4gKiAtLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLVxuICovXG5cbmNvbnN0IE1BWF9VSUQgPSAxXzAwMF8wMDBcbmNvbnN0IE1JTExJU0VDT05EU19NVUxUSVBMSUVSID0gMTAwMFxuY29uc3QgVFJBTlNJVElPTl9FTkQgPSAndHJhbnNpdGlvbmVuZCdcblxuLyoqXG4gKiBQcm9wZXJseSBlc2NhcGUgSURzIHNlbGVjdG9ycyB0byBoYW5kbGUgd2VpcmQgSURzXG4gKiBAcGFyYW0ge3N0cmluZ30gc2VsZWN0b3JcbiAqIEByZXR1cm5zIHtzdHJpbmd9XG4gKi9cbmNvbnN0IHBhcnNlU2VsZWN0b3IgPSBzZWxlY3RvciA9PiB7XG4gIGlmIChzZWxlY3RvciAmJiB3aW5kb3cuQ1NTICYmIHdpbmRvdy5DU1MuZXNjYXBlKSB7XG4gICAgLy8gZG9jdW1lbnQucXVlcnlTZWxlY3RvciBuZWVkcyBlc2NhcGluZyB0byBoYW5kbGUgSURzIChodG1sNSspIGNvbnRhaW5pbmcgZm9yIGluc3RhbmNlIC9cbiAgICBzZWxlY3RvciA9IHNlbGVjdG9yLnJlcGxhY2UoLyMoW15cXHNcIiMnXSspL2csIChtYXRjaCwgaWQpID0+IGAjJHtDU1MuZXNjYXBlKGlkKX1gKVxuICB9XG5cbiAgcmV0dXJuIHNlbGVjdG9yXG59XG5cbi8vIFNob3V0LW91dCBBbmd1cyBDcm9sbCAoaHR0cHM6Ly9nb28uZ2wvcHh3UUdwKVxuY29uc3QgdG9UeXBlID0gb2JqZWN0ID0+IHtcbiAgaWYgKG9iamVjdCA9PT0gbnVsbCB8fCBvYmplY3QgPT09IHVuZGVmaW5lZCkge1xuICAgIHJldHVybiBgJHtvYmplY3R9YFxuICB9XG5cbiAgcmV0dXJuIE9iamVjdC5wcm90b3R5cGUudG9TdHJpbmcuY2FsbChvYmplY3QpLm1hdGNoKC9cXHMoW2Etel0rKS9pKVsxXS50b0xvd2VyQ2FzZSgpXG59XG5cbi8qKlxuICogUHVibGljIFV0aWwgQVBJXG4gKi9cblxuY29uc3QgZ2V0VUlEID0gcHJlZml4ID0+IHtcbiAgZG8ge1xuICAgIHByZWZpeCArPSBNYXRoLmZsb29yKE1hdGgucmFuZG9tKCkgKiBNQVhfVUlEKVxuICB9IHdoaWxlIChkb2N1bWVudC5nZXRFbGVtZW50QnlJZChwcmVmaXgpKVxuXG4gIHJldHVybiBwcmVmaXhcbn1cblxuY29uc3QgZ2V0VHJhbnNpdGlvbkR1cmF0aW9uRnJvbUVsZW1lbnQgPSBlbGVtZW50ID0+IHtcbiAgaWYgKCFlbGVtZW50KSB7XG4gICAgcmV0dXJuIDBcbiAgfVxuXG4gIC8vIEdldCB0cmFuc2l0aW9uLWR1cmF0aW9uIG9mIHRoZSBlbGVtZW50XG4gIGxldCB7IHRyYW5zaXRpb25EdXJhdGlvbiwgdHJhbnNpdGlvbkRlbGF5IH0gPSB3aW5kb3cuZ2V0Q29tcHV0ZWRTdHlsZShlbGVtZW50KVxuXG4gIGNvbnN0IGZsb2F0VHJhbnNpdGlvbkR1cmF0aW9uID0gTnVtYmVyLnBhcnNlRmxvYXQodHJhbnNpdGlvbkR1cmF0aW9uKVxuICBjb25zdCBmbG9hdFRyYW5zaXRpb25EZWxheSA9IE51bWJlci5wYXJzZUZsb2F0KHRyYW5zaXRpb25EZWxheSlcblxuICAvLyBSZXR1cm4gMCBpZiBlbGVtZW50IG9yIHRyYW5zaXRpb24gZHVyYXRpb24gaXMgbm90IGZvdW5kXG4gIGlmICghZmxvYXRUcmFuc2l0aW9uRHVyYXRpb24gJiYgIWZsb2F0VHJhbnNpdGlvbkRlbGF5KSB7XG4gICAgcmV0dXJuIDBcbiAgfVxuXG4gIC8vIElmIG11bHRpcGxlIGR1cmF0aW9ucyBhcmUgZGVmaW5lZCwgdGFrZSB0aGUgZmlyc3RcbiAgdHJhbnNpdGlvbkR1cmF0aW9uID0gdHJhbnNpdGlvbkR1cmF0aW9uLnNwbGl0KCcsJylbMF1cbiAgdHJhbnNpdGlvbkRlbGF5ID0gdHJhbnNpdGlvbkRlbGF5LnNwbGl0KCcsJylbMF1cblxuICByZXR1cm4gKE51bWJlci5wYXJzZUZsb2F0KHRyYW5zaXRpb25EdXJhdGlvbikgKyBOdW1iZXIucGFyc2VGbG9hdCh0cmFuc2l0aW9uRGVsYXkpKSAqIE1JTExJU0VDT05EU19NVUxUSVBMSUVSXG59XG5cbmNvbnN0IHRyaWdnZXJUcmFuc2l0aW9uRW5kID0gZWxlbWVudCA9PiB7XG4gIGVsZW1lbnQuZGlzcGF0Y2hFdmVudChuZXcgRXZlbnQoVFJBTlNJVElPTl9FTkQpKVxufVxuXG5jb25zdCBpc0VsZW1lbnQgPSBvYmplY3QgPT4ge1xuICBpZiAoIW9iamVjdCB8fCB0eXBlb2Ygb2JqZWN0ICE9PSAnb2JqZWN0Jykge1xuICAgIHJldHVybiBmYWxzZVxuICB9XG5cbiAgaWYgKHR5cGVvZiBvYmplY3QuanF1ZXJ5ICE9PSAndW5kZWZpbmVkJykge1xuICAgIG9iamVjdCA9IG9iamVjdFswXVxuICB9XG5cbiAgcmV0dXJuIHR5cGVvZiBvYmplY3Qubm9kZVR5cGUgIT09ICd1bmRlZmluZWQnXG59XG5cbmNvbnN0IGdldEVsZW1lbnQgPSBvYmplY3QgPT4ge1xuICAvLyBpdCdzIGEgalF1ZXJ5IG9iamVjdCBvciBhIG5vZGUgZWxlbWVudFxuICBpZiAoaXNFbGVtZW50KG9iamVjdCkpIHtcbiAgICByZXR1cm4gb2JqZWN0LmpxdWVyeSA/IG9iamVjdFswXSA6IG9iamVjdFxuICB9XG5cbiAgaWYgKHR5cGVvZiBvYmplY3QgPT09ICdzdHJpbmcnICYmIG9iamVjdC5sZW5ndGggPiAwKSB7XG4gICAgcmV0dXJuIGRvY3VtZW50LnF1ZXJ5U2VsZWN0b3IocGFyc2VTZWxlY3RvcihvYmplY3QpKVxuICB9XG5cbiAgcmV0dXJuIG51bGxcbn1cblxuY29uc3QgaXNWaXNpYmxlID0gZWxlbWVudCA9PiB7XG4gIGlmICghaXNFbGVtZW50KGVsZW1lbnQpIHx8IGVsZW1lbnQuZ2V0Q2xpZW50UmVjdHMoKS5sZW5ndGggPT09IDApIHtcbiAgICByZXR1cm4gZmFsc2VcbiAgfVxuXG4gIGNvbnN0IGVsZW1lbnRJc1Zpc2libGUgPSBnZXRDb21wdXRlZFN0eWxlKGVsZW1lbnQpLmdldFByb3BlcnR5VmFsdWUoJ3Zpc2liaWxpdHknKSA9PT0gJ3Zpc2libGUnXG4gIC8vIEhhbmRsZSBgZGV0YWlsc2AgZWxlbWVudCBhcyBpdHMgY29udGVudCBtYXkgZmFsc2llIGFwcGVhciB2aXNpYmxlIHdoZW4gaXQgaXMgY2xvc2VkXG4gIGNvbnN0IGNsb3NlZERldGFpbHMgPSBlbGVtZW50LmNsb3Nlc3QoJ2RldGFpbHM6bm90KFtvcGVuXSknKVxuXG4gIGlmICghY2xvc2VkRGV0YWlscykge1xuICAgIHJldHVybiBlbGVtZW50SXNWaXNpYmxlXG4gIH1cblxuICBpZiAoY2xvc2VkRGV0YWlscyAhPT0gZWxlbWVudCkge1xuICAgIGNvbnN0IHN1bW1hcnkgPSBlbGVtZW50LmNsb3Nlc3QoJ3N1bW1hcnknKVxuICAgIGlmIChzdW1tYXJ5ICYmIHN1bW1hcnkucGFyZW50Tm9kZSAhPT0gY2xvc2VkRGV0YWlscykge1xuICAgICAgcmV0dXJuIGZhbHNlXG4gICAgfVxuXG4gICAgaWYgKHN1bW1hcnkgPT09IG51bGwpIHtcbiAgICAgIHJldHVybiBmYWxzZVxuICAgIH1cbiAgfVxuXG4gIHJldHVybiBlbGVtZW50SXNWaXNpYmxlXG59XG5cbmNvbnN0IGlzRGlzYWJsZWQgPSBlbGVtZW50ID0+IHtcbiAgaWYgKCFlbGVtZW50IHx8IGVsZW1lbnQubm9kZVR5cGUgIT09IE5vZGUuRUxFTUVOVF9OT0RFKSB7XG4gICAgcmV0dXJuIHRydWVcbiAgfVxuXG4gIGlmIChlbGVtZW50LmNsYXNzTGlzdC5jb250YWlucygnZGlzYWJsZWQnKSkge1xuICAgIHJldHVybiB0cnVlXG4gIH1cblxuICBpZiAodHlwZW9mIGVsZW1lbnQuZGlzYWJsZWQgIT09ICd1bmRlZmluZWQnKSB7XG4gICAgcmV0dXJuIGVsZW1lbnQuZGlzYWJsZWRcbiAgfVxuXG4gIHJldHVybiBlbGVtZW50Lmhhc0F0dHJpYnV0ZSgnZGlzYWJsZWQnKSAmJiBlbGVtZW50LmdldEF0dHJpYnV0ZSgnZGlzYWJsZWQnKSAhPT0gJ2ZhbHNlJ1xufVxuXG5jb25zdCBmaW5kU2hhZG93Um9vdCA9IGVsZW1lbnQgPT4ge1xuICBpZiAoIWRvY3VtZW50LmRvY3VtZW50RWxlbWVudC5hdHRhY2hTaGFkb3cpIHtcbiAgICByZXR1cm4gbnVsbFxuICB9XG5cbiAgLy8gQ2FuIGZpbmQgdGhlIHNoYWRvdyByb290IG90aGVyd2lzZSBpdCdsbCByZXR1cm4gdGhlIGRvY3VtZW50XG4gIGlmICh0eXBlb2YgZWxlbWVudC5nZXRSb290Tm9kZSA9PT0gJ2Z1bmN0aW9uJykge1xuICAgIGNvbnN0IHJvb3QgPSBlbGVtZW50LmdldFJvb3ROb2RlKClcbiAgICByZXR1cm4gcm9vdCBpbnN0YW5jZW9mIFNoYWRvd1Jvb3QgPyByb290IDogbnVsbFxuICB9XG5cbiAgaWYgKGVsZW1lbnQgaW5zdGFuY2VvZiBTaGFkb3dSb290KSB7XG4gICAgcmV0dXJuIGVsZW1lbnRcbiAgfVxuXG4gIC8vIHdoZW4gd2UgZG9uJ3QgZmluZCBhIHNoYWRvdyByb290XG4gIGlmICghZWxlbWVudC5wYXJlbnROb2RlKSB7XG4gICAgcmV0dXJuIG51bGxcbiAgfVxuXG4gIHJldHVybiBmaW5kU2hhZG93Um9vdChlbGVtZW50LnBhcmVudE5vZGUpXG59XG5cbmNvbnN0IG5vb3AgPSAoKSA9PiB7fVxuXG4vKipcbiAqIFRyaWNrIHRvIHJlc3RhcnQgYW4gZWxlbWVudCdzIGFuaW1hdGlvblxuICpcbiAqIEBwYXJhbSB7SFRNTEVsZW1lbnR9IGVsZW1lbnRcbiAqIEByZXR1cm4gdm9pZFxuICpcbiAqIEBzZWUgaHR0cHM6Ly93d3cuY2hhcmlzdGhlby5pby9ibG9nLzIwMjEvMDIvcmVzdGFydC1hLWNzcy1hbmltYXRpb24td2l0aC1qYXZhc2NyaXB0LyNyZXN0YXJ0aW5nLWEtY3NzLWFuaW1hdGlvblxuICovXG5jb25zdCByZWZsb3cgPSBlbGVtZW50ID0+IHtcbiAgZWxlbWVudC5vZmZzZXRIZWlnaHQgLy8gZXNsaW50LWRpc2FibGUtbGluZSBuby11bnVzZWQtZXhwcmVzc2lvbnNcbn1cblxuY29uc3QgZ2V0alF1ZXJ5ID0gKCkgPT4ge1xuICBpZiAod2luZG93LmpRdWVyeSAmJiAhZG9jdW1lbnQuYm9keS5oYXNBdHRyaWJ1dGUoJ2RhdGEtYnMtbm8tanF1ZXJ5JykpIHtcbiAgICByZXR1cm4gd2luZG93LmpRdWVyeVxuICB9XG5cbiAgcmV0dXJuIG51bGxcbn1cblxuY29uc3QgRE9NQ29udGVudExvYWRlZENhbGxiYWNrcyA9IFtdXG5cbmNvbnN0IG9uRE9NQ29udGVudExvYWRlZCA9IGNhbGxiYWNrID0+IHtcbiAgaWYgKGRvY3VtZW50LnJlYWR5U3RhdGUgPT09ICdsb2FkaW5nJykge1xuICAgIC8vIGFkZCBsaXN0ZW5lciBvbiB0aGUgZmlyc3QgY2FsbCB3aGVuIHRoZSBkb2N1bWVudCBpcyBpbiBsb2FkaW5nIHN0YXRlXG4gICAgaWYgKCFET01Db250ZW50TG9hZGVkQ2FsbGJhY2tzLmxlbmd0aCkge1xuICAgICAgZG9jdW1lbnQuYWRkRXZlbnRMaXN0ZW5lcignRE9NQ29udGVudExvYWRlZCcsICgpID0+IHtcbiAgICAgICAgZm9yIChjb25zdCBjYWxsYmFjayBvZiBET01Db250ZW50TG9hZGVkQ2FsbGJhY2tzKSB7XG4gICAgICAgICAgY2FsbGJhY2soKVxuICAgICAgICB9XG4gICAgICB9KVxuICAgIH1cblxuICAgIERPTUNvbnRlbnRMb2FkZWRDYWxsYmFja3MucHVzaChjYWxsYmFjaylcbiAgfSBlbHNlIHtcbiAgICBjYWxsYmFjaygpXG4gIH1cbn1cblxuY29uc3QgaXNSVEwgPSAoKSA9PiBkb2N1bWVudC5kb2N1bWVudEVsZW1lbnQuZGlyID09PSAncnRsJ1xuXG5jb25zdCBkZWZpbmVKUXVlcnlQbHVnaW4gPSBwbHVnaW4gPT4ge1xuICBvbkRPTUNvbnRlbnRMb2FkZWQoKCkgPT4ge1xuICAgIGNvbnN0ICQgPSBnZXRqUXVlcnkoKVxuICAgIC8qIGlzdGFuYnVsIGlnbm9yZSBpZiAqL1xuICAgIGlmICgkKSB7XG4gICAgICBjb25zdCBuYW1lID0gcGx1Z2luLk5BTUVcbiAgICAgIGNvbnN0IEpRVUVSWV9OT19DT05GTElDVCA9ICQuZm5bbmFtZV1cbiAgICAgICQuZm5bbmFtZV0gPSBwbHVnaW4ualF1ZXJ5SW50ZXJmYWNlXG4gICAgICAkLmZuW25hbWVdLkNvbnN0cnVjdG9yID0gcGx1Z2luXG4gICAgICAkLmZuW25hbWVdLm5vQ29uZmxpY3QgPSAoKSA9PiB7XG4gICAgICAgICQuZm5bbmFtZV0gPSBKUVVFUllfTk9fQ09ORkxJQ1RcbiAgICAgICAgcmV0dXJuIHBsdWdpbi5qUXVlcnlJbnRlcmZhY2VcbiAgICAgIH1cbiAgICB9XG4gIH0pXG59XG5cbmNvbnN0IGV4ZWN1dGUgPSAocG9zc2libGVDYWxsYmFjaywgYXJncyA9IFtdLCBkZWZhdWx0VmFsdWUgPSBwb3NzaWJsZUNhbGxiYWNrKSA9PiB7XG4gIHJldHVybiB0eXBlb2YgcG9zc2libGVDYWxsYmFjayA9PT0gJ2Z1bmN0aW9uJyA/IHBvc3NpYmxlQ2FsbGJhY2soLi4uYXJncykgOiBkZWZhdWx0VmFsdWVcbn1cblxuY29uc3QgZXhlY3V0ZUFmdGVyVHJhbnNpdGlvbiA9IChjYWxsYmFjaywgdHJhbnNpdGlvbkVsZW1lbnQsIHdhaXRGb3JUcmFuc2l0aW9uID0gdHJ1ZSkgPT4ge1xuICBpZiAoIXdhaXRGb3JUcmFuc2l0aW9uKSB7XG4gICAgZXhlY3V0ZShjYWxsYmFjaylcbiAgICByZXR1cm5cbiAgfVxuXG4gIGNvbnN0IGR1cmF0aW9uUGFkZGluZyA9IDVcbiAgY29uc3QgZW11bGF0ZWREdXJhdGlvbiA9IGdldFRyYW5zaXRpb25EdXJhdGlvbkZyb21FbGVtZW50KHRyYW5zaXRpb25FbGVtZW50KSArIGR1cmF0aW9uUGFkZGluZ1xuXG4gIGxldCBjYWxsZWQgPSBmYWxzZVxuXG4gIGNvbnN0IGhhbmRsZXIgPSAoeyB0YXJnZXQgfSkgPT4ge1xuICAgIGlmICh0YXJnZXQgIT09IHRyYW5zaXRpb25FbGVtZW50KSB7XG4gICAgICByZXR1cm5cbiAgICB9XG5cbiAgICBjYWxsZWQgPSB0cnVlXG4gICAgdHJhbnNpdGlvbkVsZW1lbnQucmVtb3ZlRXZlbnRMaXN0ZW5lcihUUkFOU0lUSU9OX0VORCwgaGFuZGxlcilcbiAgICBleGVjdXRlKGNhbGxiYWNrKVxuICB9XG5cbiAgdHJhbnNpdGlvbkVsZW1lbnQuYWRkRXZlbnRMaXN0ZW5lcihUUkFOU0lUSU9OX0VORCwgaGFuZGxlcilcbiAgc2V0VGltZW91dCgoKSA9PiB7XG4gICAgaWYgKCFjYWxsZWQpIHtcbiAgICAgIHRyaWdnZXJUcmFuc2l0aW9uRW5kKHRyYW5zaXRpb25FbGVtZW50KVxuICAgIH1cbiAgfSwgZW11bGF0ZWREdXJhdGlvbilcbn1cblxuLyoqXG4gKiBSZXR1cm4gdGhlIHByZXZpb3VzL25leHQgZWxlbWVudCBvZiBhIGxpc3QuXG4gKlxuICogQHBhcmFtIHthcnJheX0gbGlzdCAgICBUaGUgbGlzdCBvZiBlbGVtZW50c1xuICogQHBhcmFtIGFjdGl2ZUVsZW1lbnQgICBUaGUgYWN0aXZlIGVsZW1lbnRcbiAqIEBwYXJhbSBzaG91bGRHZXROZXh0ICAgQ2hvb3NlIHRvIGdldCBuZXh0IG9yIHByZXZpb3VzIGVsZW1lbnRcbiAqIEBwYXJhbSBpc0N5Y2xlQWxsb3dlZFxuICogQHJldHVybiB7RWxlbWVudHxlbGVtfSBUaGUgcHJvcGVyIGVsZW1lbnRcbiAqL1xuY29uc3QgZ2V0TmV4dEFjdGl2ZUVsZW1lbnQgPSAobGlzdCwgYWN0aXZlRWxlbWVudCwgc2hvdWxkR2V0TmV4dCwgaXNDeWNsZUFsbG93ZWQpID0+IHtcbiAgY29uc3QgbGlzdExlbmd0aCA9IGxpc3QubGVuZ3RoXG4gIGxldCBpbmRleCA9IGxpc3QuaW5kZXhPZihhY3RpdmVFbGVtZW50KVxuXG4gIC8vIGlmIHRoZSBlbGVtZW50IGRvZXMgbm90IGV4aXN0IGluIHRoZSBsaXN0IHJldHVybiBhbiBlbGVtZW50XG4gIC8vIGRlcGVuZGluZyBvbiB0aGUgZGlyZWN0aW9uIGFuZCBpZiBjeWNsZSBpcyBhbGxvd2VkXG4gIGlmIChpbmRleCA9PT0gLTEpIHtcbiAgICByZXR1cm4gIXNob3VsZEdldE5leHQgJiYgaXNDeWNsZUFsbG93ZWQgPyBsaXN0W2xpc3RMZW5ndGggLSAxXSA6IGxpc3RbMF1cbiAgfVxuXG4gIGluZGV4ICs9IHNob3VsZEdldE5leHQgPyAxIDogLTFcblxuICBpZiAoaXNDeWNsZUFsbG93ZWQpIHtcbiAgICBpbmRleCA9IChpbmRleCArIGxpc3RMZW5ndGgpICUgbGlzdExlbmd0aFxuICB9XG5cbiAgcmV0dXJuIGxpc3RbTWF0aC5tYXgoMCwgTWF0aC5taW4oaW5kZXgsIGxpc3RMZW5ndGggLSAxKSldXG59XG5cbmV4cG9ydCB7XG4gIGRlZmluZUpRdWVyeVBsdWdpbixcbiAgZXhlY3V0ZSxcbiAgZXhlY3V0ZUFmdGVyVHJhbnNpdGlvbixcbiAgZmluZFNoYWRvd1Jvb3QsXG4gIGdldEVsZW1lbnQsXG4gIGdldGpRdWVyeSxcbiAgZ2V0TmV4dEFjdGl2ZUVsZW1lbnQsXG4gIGdldFRyYW5zaXRpb25EdXJhdGlvbkZyb21FbGVtZW50LFxuICBnZXRVSUQsXG4gIGlzRGlzYWJsZWQsXG4gIGlzRWxlbWVudCxcbiAgaXNSVEwsXG4gIGlzVmlzaWJsZSxcbiAgbm9vcCxcbiAgb25ET01Db250ZW50TG9hZGVkLFxuICBwYXJzZVNlbGVjdG9yLFxuICByZWZsb3csXG4gIHRyaWdnZXJUcmFuc2l0aW9uRW5kLFxuICB0b1R5cGVcbn1cbiIsICIvKipcbiAqIC0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tXG4gKiBCb290c3RyYXAgZG9tL2V2ZW50LWhhbmRsZXIuanNcbiAqIExpY2Vuc2VkIHVuZGVyIE1JVCAoaHR0cHM6Ly9naXRodWIuY29tL3R3YnMvYm9vdHN0cmFwL2Jsb2IvbWFpbi9MSUNFTlNFKVxuICogLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS1cbiAqL1xuXG5pbXBvcnQgeyBnZXRqUXVlcnkgfSBmcm9tICcuLi91dGlsL2luZGV4LmpzJ1xuXG4vKipcbiAqIENvbnN0YW50c1xuICovXG5cbmNvbnN0IG5hbWVzcGFjZVJlZ2V4ID0gL1teLl0qKD89XFwuLiopXFwufC4qL1xuY29uc3Qgc3RyaXBOYW1lUmVnZXggPSAvXFwuLiovXG5jb25zdCBzdHJpcFVpZFJlZ2V4ID0gLzo6XFxkKyQvXG5jb25zdCBldmVudFJlZ2lzdHJ5ID0ge30gLy8gRXZlbnRzIHN0b3JhZ2VcbmxldCB1aWRFdmVudCA9IDFcbmNvbnN0IGN1c3RvbUV2ZW50cyA9IHtcbiAgbW91c2VlbnRlcjogJ21vdXNlb3ZlcicsXG4gIG1vdXNlbGVhdmU6ICdtb3VzZW91dCdcbn1cblxuY29uc3QgbmF0aXZlRXZlbnRzID0gbmV3IFNldChbXG4gICdjbGljaycsXG4gICdkYmxjbGljaycsXG4gICdtb3VzZXVwJyxcbiAgJ21vdXNlZG93bicsXG4gICdjb250ZXh0bWVudScsXG4gICdtb3VzZXdoZWVsJyxcbiAgJ0RPTU1vdXNlU2Nyb2xsJyxcbiAgJ21vdXNlb3ZlcicsXG4gICdtb3VzZW91dCcsXG4gICdtb3VzZW1vdmUnLFxuICAnc2VsZWN0c3RhcnQnLFxuICAnc2VsZWN0ZW5kJyxcbiAgJ2tleWRvd24nLFxuICAna2V5cHJlc3MnLFxuICAna2V5dXAnLFxuICAnb3JpZW50YXRpb25jaGFuZ2UnLFxuICAndG91Y2hzdGFydCcsXG4gICd0b3VjaG1vdmUnLFxuICAndG91Y2hlbmQnLFxuICAndG91Y2hjYW5jZWwnLFxuICAncG9pbnRlcmRvd24nLFxuICAncG9pbnRlcm1vdmUnLFxuICAncG9pbnRlcnVwJyxcbiAgJ3BvaW50ZXJsZWF2ZScsXG4gICdwb2ludGVyY2FuY2VsJyxcbiAgJ2dlc3R1cmVzdGFydCcsXG4gICdnZXN0dXJlY2hhbmdlJyxcbiAgJ2dlc3R1cmVlbmQnLFxuICAnZm9jdXMnLFxuICAnYmx1cicsXG4gICdjaGFuZ2UnLFxuICAncmVzZXQnLFxuICAnc2VsZWN0JyxcbiAgJ3N1Ym1pdCcsXG4gICdmb2N1c2luJyxcbiAgJ2ZvY3Vzb3V0JyxcbiAgJ2xvYWQnLFxuICAndW5sb2FkJyxcbiAgJ2JlZm9yZXVubG9hZCcsXG4gICdyZXNpemUnLFxuICAnbW92ZScsXG4gICdET01Db250ZW50TG9hZGVkJyxcbiAgJ3JlYWR5c3RhdGVjaGFuZ2UnLFxuICAnZXJyb3InLFxuICAnYWJvcnQnLFxuICAnc2Nyb2xsJ1xuXSlcblxuLyoqXG4gKiBQcml2YXRlIG1ldGhvZHNcbiAqL1xuXG5mdW5jdGlvbiBtYWtlRXZlbnRVaWQoZWxlbWVudCwgdWlkKSB7XG4gIHJldHVybiAodWlkICYmIGAke3VpZH06OiR7dWlkRXZlbnQrK31gKSB8fCBlbGVtZW50LnVpZEV2ZW50IHx8IHVpZEV2ZW50Kytcbn1cblxuZnVuY3Rpb24gZ2V0RWxlbWVudEV2ZW50cyhlbGVtZW50KSB7XG4gIGNvbnN0IHVpZCA9IG1ha2VFdmVudFVpZChlbGVtZW50KVxuXG4gIGVsZW1lbnQudWlkRXZlbnQgPSB1aWRcbiAgZXZlbnRSZWdpc3RyeVt1aWRdID0gZXZlbnRSZWdpc3RyeVt1aWRdIHx8IHt9XG5cbiAgcmV0dXJuIGV2ZW50UmVnaXN0cnlbdWlkXVxufVxuXG5mdW5jdGlvbiBib290c3RyYXBIYW5kbGVyKGVsZW1lbnQsIGZuKSB7XG4gIHJldHVybiBmdW5jdGlvbiBoYW5kbGVyKGV2ZW50KSB7XG4gICAgaHlkcmF0ZU9iaihldmVudCwgeyBkZWxlZ2F0ZVRhcmdldDogZWxlbWVudCB9KVxuXG4gICAgaWYgKGhhbmRsZXIub25lT2ZmKSB7XG4gICAgICBFdmVudEhhbmRsZXIub2ZmKGVsZW1lbnQsIGV2ZW50LnR5cGUsIGZuKVxuICAgIH1cblxuICAgIHJldHVybiBmbi5hcHBseShlbGVtZW50LCBbZXZlbnRdKVxuICB9XG59XG5cbmZ1bmN0aW9uIGJvb3RzdHJhcERlbGVnYXRpb25IYW5kbGVyKGVsZW1lbnQsIHNlbGVjdG9yLCBmbikge1xuICByZXR1cm4gZnVuY3Rpb24gaGFuZGxlcihldmVudCkge1xuICAgIGNvbnN0IGRvbUVsZW1lbnRzID0gZWxlbWVudC5xdWVyeVNlbGVjdG9yQWxsKHNlbGVjdG9yKVxuXG4gICAgZm9yIChsZXQgeyB0YXJnZXQgfSA9IGV2ZW50OyB0YXJnZXQgJiYgdGFyZ2V0ICE9PSB0aGlzOyB0YXJnZXQgPSB0YXJnZXQucGFyZW50Tm9kZSkge1xuICAgICAgZm9yIChjb25zdCBkb21FbGVtZW50IG9mIGRvbUVsZW1lbnRzKSB7XG4gICAgICAgIGlmIChkb21FbGVtZW50ICE9PSB0YXJnZXQpIHtcbiAgICAgICAgICBjb250aW51ZVxuICAgICAgICB9XG5cbiAgICAgICAgaHlkcmF0ZU9iaihldmVudCwgeyBkZWxlZ2F0ZVRhcmdldDogdGFyZ2V0IH0pXG5cbiAgICAgICAgaWYgKGhhbmRsZXIub25lT2ZmKSB7XG4gICAgICAgICAgRXZlbnRIYW5kbGVyLm9mZihlbGVtZW50LCBldmVudC50eXBlLCBzZWxlY3RvciwgZm4pXG4gICAgICAgIH1cblxuICAgICAgICByZXR1cm4gZm4uYXBwbHkodGFyZ2V0LCBbZXZlbnRdKVxuICAgICAgfVxuICAgIH1cbiAgfVxufVxuXG5mdW5jdGlvbiBmaW5kSGFuZGxlcihldmVudHMsIGNhbGxhYmxlLCBkZWxlZ2F0aW9uU2VsZWN0b3IgPSBudWxsKSB7XG4gIHJldHVybiBPYmplY3QudmFsdWVzKGV2ZW50cylcbiAgICAuZmluZChldmVudCA9PiBldmVudC5jYWxsYWJsZSA9PT0gY2FsbGFibGUgJiYgZXZlbnQuZGVsZWdhdGlvblNlbGVjdG9yID09PSBkZWxlZ2F0aW9uU2VsZWN0b3IpXG59XG5cbmZ1bmN0aW9uIG5vcm1hbGl6ZVBhcmFtZXRlcnMob3JpZ2luYWxUeXBlRXZlbnQsIGhhbmRsZXIsIGRlbGVnYXRpb25GdW5jdGlvbikge1xuICBjb25zdCBpc0RlbGVnYXRlZCA9IHR5cGVvZiBoYW5kbGVyID09PSAnc3RyaW5nJ1xuICAvLyBUT0RPOiB0b29sdGlwIHBhc3NlcyBgZmFsc2VgIGluc3RlYWQgb2Ygc2VsZWN0b3IsIHNvIHdlIG5lZWQgdG8gY2hlY2tcbiAgY29uc3QgY2FsbGFibGUgPSBpc0RlbGVnYXRlZCA/IGRlbGVnYXRpb25GdW5jdGlvbiA6IChoYW5kbGVyIHx8IGRlbGVnYXRpb25GdW5jdGlvbilcbiAgbGV0IHR5cGVFdmVudCA9IGdldFR5cGVFdmVudChvcmlnaW5hbFR5cGVFdmVudClcblxuICBpZiAoIW5hdGl2ZUV2ZW50cy5oYXModHlwZUV2ZW50KSkge1xuICAgIHR5cGVFdmVudCA9IG9yaWdpbmFsVHlwZUV2ZW50XG4gIH1cblxuICByZXR1cm4gW2lzRGVsZWdhdGVkLCBjYWxsYWJsZSwgdHlwZUV2ZW50XVxufVxuXG5mdW5jdGlvbiBhZGRIYW5kbGVyKGVsZW1lbnQsIG9yaWdpbmFsVHlwZUV2ZW50LCBoYW5kbGVyLCBkZWxlZ2F0aW9uRnVuY3Rpb24sIG9uZU9mZikge1xuICBpZiAodHlwZW9mIG9yaWdpbmFsVHlwZUV2ZW50ICE9PSAnc3RyaW5nJyB8fCAhZWxlbWVudCkge1xuICAgIHJldHVyblxuICB9XG5cbiAgbGV0IFtpc0RlbGVnYXRlZCwgY2FsbGFibGUsIHR5cGVFdmVudF0gPSBub3JtYWxpemVQYXJhbWV0ZXJzKG9yaWdpbmFsVHlwZUV2ZW50LCBoYW5kbGVyLCBkZWxlZ2F0aW9uRnVuY3Rpb24pXG5cbiAgLy8gaW4gY2FzZSBvZiBtb3VzZWVudGVyIG9yIG1vdXNlbGVhdmUgd3JhcCB0aGUgaGFuZGxlciB3aXRoaW4gYSBmdW5jdGlvbiB0aGF0IGNoZWNrcyBmb3IgaXRzIERPTSBwb3NpdGlvblxuICAvLyB0aGlzIHByZXZlbnRzIHRoZSBoYW5kbGVyIGZyb20gYmVpbmcgZGlzcGF0Y2hlZCB0aGUgc2FtZSB3YXkgYXMgbW91c2VvdmVyIG9yIG1vdXNlb3V0IGRvZXNcbiAgaWYgKG9yaWdpbmFsVHlwZUV2ZW50IGluIGN1c3RvbUV2ZW50cykge1xuICAgIGNvbnN0IHdyYXBGdW5jdGlvbiA9IGZuID0+IHtcbiAgICAgIHJldHVybiBmdW5jdGlvbiAoZXZlbnQpIHtcbiAgICAgICAgaWYgKCFldmVudC5yZWxhdGVkVGFyZ2V0IHx8IChldmVudC5yZWxhdGVkVGFyZ2V0ICE9PSBldmVudC5kZWxlZ2F0ZVRhcmdldCAmJiAhZXZlbnQuZGVsZWdhdGVUYXJnZXQuY29udGFpbnMoZXZlbnQucmVsYXRlZFRhcmdldCkpKSB7XG4gICAgICAgICAgcmV0dXJuIGZuLmNhbGwodGhpcywgZXZlbnQpXG4gICAgICAgIH1cbiAgICAgIH1cbiAgICB9XG5cbiAgICBjYWxsYWJsZSA9IHdyYXBGdW5jdGlvbihjYWxsYWJsZSlcbiAgfVxuXG4gIGNvbnN0IGV2ZW50cyA9IGdldEVsZW1lbnRFdmVudHMoZWxlbWVudClcbiAgY29uc3QgaGFuZGxlcnMgPSBldmVudHNbdHlwZUV2ZW50XSB8fCAoZXZlbnRzW3R5cGVFdmVudF0gPSB7fSlcbiAgY29uc3QgcHJldmlvdXNGdW5jdGlvbiA9IGZpbmRIYW5kbGVyKGhhbmRsZXJzLCBjYWxsYWJsZSwgaXNEZWxlZ2F0ZWQgPyBoYW5kbGVyIDogbnVsbClcblxuICBpZiAocHJldmlvdXNGdW5jdGlvbikge1xuICAgIHByZXZpb3VzRnVuY3Rpb24ub25lT2ZmID0gcHJldmlvdXNGdW5jdGlvbi5vbmVPZmYgJiYgb25lT2ZmXG5cbiAgICByZXR1cm5cbiAgfVxuXG4gIGNvbnN0IHVpZCA9IG1ha2VFdmVudFVpZChjYWxsYWJsZSwgb3JpZ2luYWxUeXBlRXZlbnQucmVwbGFjZShuYW1lc3BhY2VSZWdleCwgJycpKVxuICBjb25zdCBmbiA9IGlzRGVsZWdhdGVkID9cbiAgICBib290c3RyYXBEZWxlZ2F0aW9uSGFuZGxlcihlbGVtZW50LCBoYW5kbGVyLCBjYWxsYWJsZSkgOlxuICAgIGJvb3RzdHJhcEhhbmRsZXIoZWxlbWVudCwgY2FsbGFibGUpXG5cbiAgZm4uZGVsZWdhdGlvblNlbGVjdG9yID0gaXNEZWxlZ2F0ZWQgPyBoYW5kbGVyIDogbnVsbFxuICBmbi5jYWxsYWJsZSA9IGNhbGxhYmxlXG4gIGZuLm9uZU9mZiA9IG9uZU9mZlxuICBmbi51aWRFdmVudCA9IHVpZFxuICBoYW5kbGVyc1t1aWRdID0gZm5cblxuICBlbGVtZW50LmFkZEV2ZW50TGlzdGVuZXIodHlwZUV2ZW50LCBmbiwgaXNEZWxlZ2F0ZWQpXG59XG5cbmZ1bmN0aW9uIHJlbW92ZUhhbmRsZXIoZWxlbWVudCwgZXZlbnRzLCB0eXBlRXZlbnQsIGhhbmRsZXIsIGRlbGVnYXRpb25TZWxlY3Rvcikge1xuICBjb25zdCBmbiA9IGZpbmRIYW5kbGVyKGV2ZW50c1t0eXBlRXZlbnRdLCBoYW5kbGVyLCBkZWxlZ2F0aW9uU2VsZWN0b3IpXG5cbiAgaWYgKCFmbikge1xuICAgIHJldHVyblxuICB9XG5cbiAgZWxlbWVudC5yZW1vdmVFdmVudExpc3RlbmVyKHR5cGVFdmVudCwgZm4sIEJvb2xlYW4oZGVsZWdhdGlvblNlbGVjdG9yKSlcbiAgZGVsZXRlIGV2ZW50c1t0eXBlRXZlbnRdW2ZuLnVpZEV2ZW50XVxufVxuXG5mdW5jdGlvbiByZW1vdmVOYW1lc3BhY2VkSGFuZGxlcnMoZWxlbWVudCwgZXZlbnRzLCB0eXBlRXZlbnQsIG5hbWVzcGFjZSkge1xuICBjb25zdCBzdG9yZUVsZW1lbnRFdmVudCA9IGV2ZW50c1t0eXBlRXZlbnRdIHx8IHt9XG5cbiAgZm9yIChjb25zdCBbaGFuZGxlcktleSwgZXZlbnRdIG9mIE9iamVjdC5lbnRyaWVzKHN0b3JlRWxlbWVudEV2ZW50KSkge1xuICAgIGlmIChoYW5kbGVyS2V5LmluY2x1ZGVzKG5hbWVzcGFjZSkpIHtcbiAgICAgIHJlbW92ZUhhbmRsZXIoZWxlbWVudCwgZXZlbnRzLCB0eXBlRXZlbnQsIGV2ZW50LmNhbGxhYmxlLCBldmVudC5kZWxlZ2F0aW9uU2VsZWN0b3IpXG4gICAgfVxuICB9XG59XG5cbmZ1bmN0aW9uIGdldFR5cGVFdmVudChldmVudCkge1xuICAvLyBhbGxvdyB0byBnZXQgdGhlIG5hdGl2ZSBldmVudHMgZnJvbSBuYW1lc3BhY2VkIGV2ZW50cyAoJ2NsaWNrLmJzLmJ1dHRvbicgLS0+ICdjbGljaycpXG4gIGV2ZW50ID0gZXZlbnQucmVwbGFjZShzdHJpcE5hbWVSZWdleCwgJycpXG4gIHJldHVybiBjdXN0b21FdmVudHNbZXZlbnRdIHx8IGV2ZW50XG59XG5cbmNvbnN0IEV2ZW50SGFuZGxlciA9IHtcbiAgb24oZWxlbWVudCwgZXZlbnQsIGhhbmRsZXIsIGRlbGVnYXRpb25GdW5jdGlvbikge1xuICAgIGFkZEhhbmRsZXIoZWxlbWVudCwgZXZlbnQsIGhhbmRsZXIsIGRlbGVnYXRpb25GdW5jdGlvbiwgZmFsc2UpXG4gIH0sXG5cbiAgb25lKGVsZW1lbnQsIGV2ZW50LCBoYW5kbGVyLCBkZWxlZ2F0aW9uRnVuY3Rpb24pIHtcbiAgICBhZGRIYW5kbGVyKGVsZW1lbnQsIGV2ZW50LCBoYW5kbGVyLCBkZWxlZ2F0aW9uRnVuY3Rpb24sIHRydWUpXG4gIH0sXG5cbiAgb2ZmKGVsZW1lbnQsIG9yaWdpbmFsVHlwZUV2ZW50LCBoYW5kbGVyLCBkZWxlZ2F0aW9uRnVuY3Rpb24pIHtcbiAgICBpZiAodHlwZW9mIG9yaWdpbmFsVHlwZUV2ZW50ICE9PSAnc3RyaW5nJyB8fCAhZWxlbWVudCkge1xuICAgICAgcmV0dXJuXG4gICAgfVxuXG4gICAgY29uc3QgW2lzRGVsZWdhdGVkLCBjYWxsYWJsZSwgdHlwZUV2ZW50XSA9IG5vcm1hbGl6ZVBhcmFtZXRlcnMob3JpZ2luYWxUeXBlRXZlbnQsIGhhbmRsZXIsIGRlbGVnYXRpb25GdW5jdGlvbilcbiAgICBjb25zdCBpbk5hbWVzcGFjZSA9IHR5cGVFdmVudCAhPT0gb3JpZ2luYWxUeXBlRXZlbnRcbiAgICBjb25zdCBldmVudHMgPSBnZXRFbGVtZW50RXZlbnRzKGVsZW1lbnQpXG4gICAgY29uc3Qgc3RvcmVFbGVtZW50RXZlbnQgPSBldmVudHNbdHlwZUV2ZW50XSB8fCB7fVxuICAgIGNvbnN0IGlzTmFtZXNwYWNlID0gb3JpZ2luYWxUeXBlRXZlbnQuc3RhcnRzV2l0aCgnLicpXG5cbiAgICBpZiAodHlwZW9mIGNhbGxhYmxlICE9PSAndW5kZWZpbmVkJykge1xuICAgICAgLy8gU2ltcGxlc3QgY2FzZTogaGFuZGxlciBpcyBwYXNzZWQsIHJlbW92ZSB0aGF0IGxpc3RlbmVyIE9OTFkuXG4gICAgICBpZiAoIU9iamVjdC5rZXlzKHN0b3JlRWxlbWVudEV2ZW50KS5sZW5ndGgpIHtcbiAgICAgICAgcmV0dXJuXG4gICAgICB9XG5cbiAgICAgIHJlbW92ZUhhbmRsZXIoZWxlbWVudCwgZXZlbnRzLCB0eXBlRXZlbnQsIGNhbGxhYmxlLCBpc0RlbGVnYXRlZCA/IGhhbmRsZXIgOiBudWxsKVxuICAgICAgcmV0dXJuXG4gICAgfVxuXG4gICAgaWYgKGlzTmFtZXNwYWNlKSB7XG4gICAgICBmb3IgKGNvbnN0IGVsZW1lbnRFdmVudCBvZiBPYmplY3Qua2V5cyhldmVudHMpKSB7XG4gICAgICAgIHJlbW92ZU5hbWVzcGFjZWRIYW5kbGVycyhlbGVtZW50LCBldmVudHMsIGVsZW1lbnRFdmVudCwgb3JpZ2luYWxUeXBlRXZlbnQuc2xpY2UoMSkpXG4gICAgICB9XG4gICAgfVxuXG4gICAgZm9yIChjb25zdCBba2V5SGFuZGxlcnMsIGV2ZW50XSBvZiBPYmplY3QuZW50cmllcyhzdG9yZUVsZW1lbnRFdmVudCkpIHtcbiAgICAgIGNvbnN0IGhhbmRsZXJLZXkgPSBrZXlIYW5kbGVycy5yZXBsYWNlKHN0cmlwVWlkUmVnZXgsICcnKVxuXG4gICAgICBpZiAoIWluTmFtZXNwYWNlIHx8IG9yaWdpbmFsVHlwZUV2ZW50LmluY2x1ZGVzKGhhbmRsZXJLZXkpKSB7XG4gICAgICAgIHJlbW92ZUhhbmRsZXIoZWxlbWVudCwgZXZlbnRzLCB0eXBlRXZlbnQsIGV2ZW50LmNhbGxhYmxlLCBldmVudC5kZWxlZ2F0aW9uU2VsZWN0b3IpXG4gICAgICB9XG4gICAgfVxuICB9LFxuXG4gIHRyaWdnZXIoZWxlbWVudCwgZXZlbnQsIGFyZ3MpIHtcbiAgICBpZiAodHlwZW9mIGV2ZW50ICE9PSAnc3RyaW5nJyB8fCAhZWxlbWVudCkge1xuICAgICAgcmV0dXJuIG51bGxcbiAgICB9XG5cbiAgICBjb25zdCAkID0gZ2V0alF1ZXJ5KClcbiAgICBjb25zdCB0eXBlRXZlbnQgPSBnZXRUeXBlRXZlbnQoZXZlbnQpXG4gICAgY29uc3QgaW5OYW1lc3BhY2UgPSBldmVudCAhPT0gdHlwZUV2ZW50XG5cbiAgICBsZXQgalF1ZXJ5RXZlbnQgPSBudWxsXG4gICAgbGV0IGJ1YmJsZXMgPSB0cnVlXG4gICAgbGV0IG5hdGl2ZURpc3BhdGNoID0gdHJ1ZVxuICAgIGxldCBkZWZhdWx0UHJldmVudGVkID0gZmFsc2VcblxuICAgIGlmIChpbk5hbWVzcGFjZSAmJiAkKSB7XG4gICAgICBqUXVlcnlFdmVudCA9ICQuRXZlbnQoZXZlbnQsIGFyZ3MpXG5cbiAgICAgICQoZWxlbWVudCkudHJpZ2dlcihqUXVlcnlFdmVudClcbiAgICAgIGJ1YmJsZXMgPSAhalF1ZXJ5RXZlbnQuaXNQcm9wYWdhdGlvblN0b3BwZWQoKVxuICAgICAgbmF0aXZlRGlzcGF0Y2ggPSAhalF1ZXJ5RXZlbnQuaXNJbW1lZGlhdGVQcm9wYWdhdGlvblN0b3BwZWQoKVxuICAgICAgZGVmYXVsdFByZXZlbnRlZCA9IGpRdWVyeUV2ZW50LmlzRGVmYXVsdFByZXZlbnRlZCgpXG4gICAgfVxuXG4gICAgY29uc3QgZXZ0ID0gaHlkcmF0ZU9iaihuZXcgRXZlbnQoZXZlbnQsIHsgYnViYmxlcywgY2FuY2VsYWJsZTogdHJ1ZSB9KSwgYXJncylcblxuICAgIGlmIChkZWZhdWx0UHJldmVudGVkKSB7XG4gICAgICBldnQucHJldmVudERlZmF1bHQoKVxuICAgIH1cblxuICAgIGlmIChuYXRpdmVEaXNwYXRjaCkge1xuICAgICAgZWxlbWVudC5kaXNwYXRjaEV2ZW50KGV2dClcbiAgICB9XG5cbiAgICBpZiAoZXZ0LmRlZmF1bHRQcmV2ZW50ZWQgJiYgalF1ZXJ5RXZlbnQpIHtcbiAgICAgIGpRdWVyeUV2ZW50LnByZXZlbnREZWZhdWx0KClcbiAgICB9XG5cbiAgICByZXR1cm4gZXZ0XG4gIH1cbn1cblxuZnVuY3Rpb24gaHlkcmF0ZU9iaihvYmosIG1ldGEgPSB7fSkge1xuICBmb3IgKGNvbnN0IFtrZXksIHZhbHVlXSBvZiBPYmplY3QuZW50cmllcyhtZXRhKSkge1xuICAgIHRyeSB7XG4gICAgICBvYmpba2V5XSA9IHZhbHVlXG4gICAgfSBjYXRjaCB7XG4gICAgICBPYmplY3QuZGVmaW5lUHJvcGVydHkob2JqLCBrZXksIHtcbiAgICAgICAgY29uZmlndXJhYmxlOiB0cnVlLFxuICAgICAgICBnZXQoKSB7XG4gICAgICAgICAgcmV0dXJuIHZhbHVlXG4gICAgICAgIH1cbiAgICAgIH0pXG4gICAgfVxuICB9XG5cbiAgcmV0dXJuIG9ialxufVxuXG5leHBvcnQgZGVmYXVsdCBFdmVudEhhbmRsZXJcbiIsICIvKipcbiAqIC0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tXG4gKiBCb290c3RyYXAgZG9tL21hbmlwdWxhdG9yLmpzXG4gKiBMaWNlbnNlZCB1bmRlciBNSVQgKGh0dHBzOi8vZ2l0aHViLmNvbS90d2JzL2Jvb3RzdHJhcC9ibG9iL21haW4vTElDRU5TRSlcbiAqIC0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tXG4gKi9cblxuZnVuY3Rpb24gbm9ybWFsaXplRGF0YSh2YWx1ZSkge1xuICBpZiAodmFsdWUgPT09ICd0cnVlJykge1xuICAgIHJldHVybiB0cnVlXG4gIH1cblxuICBpZiAodmFsdWUgPT09ICdmYWxzZScpIHtcbiAgICByZXR1cm4gZmFsc2VcbiAgfVxuXG4gIGlmICh2YWx1ZSA9PT0gTnVtYmVyKHZhbHVlKS50b1N0cmluZygpKSB7XG4gICAgcmV0dXJuIE51bWJlcih2YWx1ZSlcbiAgfVxuXG4gIGlmICh2YWx1ZSA9PT0gJycgfHwgdmFsdWUgPT09ICdudWxsJykge1xuICAgIHJldHVybiBudWxsXG4gIH1cblxuICBpZiAodHlwZW9mIHZhbHVlICE9PSAnc3RyaW5nJykge1xuICAgIHJldHVybiB2YWx1ZVxuICB9XG5cbiAgdHJ5IHtcbiAgICByZXR1cm4gSlNPTi5wYXJzZShkZWNvZGVVUklDb21wb25lbnQodmFsdWUpKVxuICB9IGNhdGNoIHtcbiAgICByZXR1cm4gdmFsdWVcbiAgfVxufVxuXG5mdW5jdGlvbiBub3JtYWxpemVEYXRhS2V5KGtleSkge1xuICByZXR1cm4ga2V5LnJlcGxhY2UoL1tBLVpdL2csIGNociA9PiBgLSR7Y2hyLnRvTG93ZXJDYXNlKCl9YClcbn1cblxuY29uc3QgTWFuaXB1bGF0b3IgPSB7XG4gIHNldERhdGFBdHRyaWJ1dGUoZWxlbWVudCwga2V5LCB2YWx1ZSkge1xuICAgIGVsZW1lbnQuc2V0QXR0cmlidXRlKGBkYXRhLWJzLSR7bm9ybWFsaXplRGF0YUtleShrZXkpfWAsIHZhbHVlKVxuICB9LFxuXG4gIHJlbW92ZURhdGFBdHRyaWJ1dGUoZWxlbWVudCwga2V5KSB7XG4gICAgZWxlbWVudC5yZW1vdmVBdHRyaWJ1dGUoYGRhdGEtYnMtJHtub3JtYWxpemVEYXRhS2V5KGtleSl9YClcbiAgfSxcblxuICBnZXREYXRhQXR0cmlidXRlcyhlbGVtZW50KSB7XG4gICAgaWYgKCFlbGVtZW50KSB7XG4gICAgICByZXR1cm4ge31cbiAgICB9XG5cbiAgICBjb25zdCBhdHRyaWJ1dGVzID0ge31cbiAgICBjb25zdCBic0tleXMgPSBPYmplY3Qua2V5cyhlbGVtZW50LmRhdGFzZXQpLmZpbHRlcihrZXkgPT4ga2V5LnN0YXJ0c1dpdGgoJ2JzJykgJiYgIWtleS5zdGFydHNXaXRoKCdic0NvbmZpZycpKVxuXG4gICAgZm9yIChjb25zdCBrZXkgb2YgYnNLZXlzKSB7XG4gICAgICBsZXQgcHVyZUtleSA9IGtleS5yZXBsYWNlKC9eYnMvLCAnJylcbiAgICAgIHB1cmVLZXkgPSBwdXJlS2V5LmNoYXJBdCgwKS50b0xvd2VyQ2FzZSgpICsgcHVyZUtleS5zbGljZSgxLCBwdXJlS2V5Lmxlbmd0aClcbiAgICAgIGF0dHJpYnV0ZXNbcHVyZUtleV0gPSBub3JtYWxpemVEYXRhKGVsZW1lbnQuZGF0YXNldFtrZXldKVxuICAgIH1cblxuICAgIHJldHVybiBhdHRyaWJ1dGVzXG4gIH0sXG5cbiAgZ2V0RGF0YUF0dHJpYnV0ZShlbGVtZW50LCBrZXkpIHtcbiAgICByZXR1cm4gbm9ybWFsaXplRGF0YShlbGVtZW50LmdldEF0dHJpYnV0ZShgZGF0YS1icy0ke25vcm1hbGl6ZURhdGFLZXkoa2V5KX1gKSlcbiAgfVxufVxuXG5leHBvcnQgZGVmYXVsdCBNYW5pcHVsYXRvclxuIiwgIi8qKlxuICogLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS1cbiAqIEJvb3RzdHJhcCB1dGlsL2NvbmZpZy5qc1xuICogTGljZW5zZWQgdW5kZXIgTUlUIChodHRwczovL2dpdGh1Yi5jb20vdHdicy9ib290c3RyYXAvYmxvYi9tYWluL0xJQ0VOU0UpXG4gKiAtLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLVxuICovXG5cbmltcG9ydCBNYW5pcHVsYXRvciBmcm9tICcuLi9kb20vbWFuaXB1bGF0b3IuanMnXG5pbXBvcnQgeyBpc0VsZW1lbnQsIHRvVHlwZSB9IGZyb20gJy4vaW5kZXguanMnXG5cbi8qKlxuICogQ2xhc3MgZGVmaW5pdGlvblxuICovXG5cbmNsYXNzIENvbmZpZyB7XG4gIC8vIEdldHRlcnNcbiAgc3RhdGljIGdldCBEZWZhdWx0KCkge1xuICAgIHJldHVybiB7fVxuICB9XG5cbiAgc3RhdGljIGdldCBEZWZhdWx0VHlwZSgpIHtcbiAgICByZXR1cm4ge31cbiAgfVxuXG4gIHN0YXRpYyBnZXQgTkFNRSgpIHtcbiAgICB0aHJvdyBuZXcgRXJyb3IoJ1lvdSBoYXZlIHRvIGltcGxlbWVudCB0aGUgc3RhdGljIG1ldGhvZCBcIk5BTUVcIiwgZm9yIGVhY2ggY29tcG9uZW50IScpXG4gIH1cblxuICBfZ2V0Q29uZmlnKGNvbmZpZykge1xuICAgIGNvbmZpZyA9IHRoaXMuX21lcmdlQ29uZmlnT2JqKGNvbmZpZylcbiAgICBjb25maWcgPSB0aGlzLl9jb25maWdBZnRlck1lcmdlKGNvbmZpZylcbiAgICB0aGlzLl90eXBlQ2hlY2tDb25maWcoY29uZmlnKVxuICAgIHJldHVybiBjb25maWdcbiAgfVxuXG4gIF9jb25maWdBZnRlck1lcmdlKGNvbmZpZykge1xuICAgIHJldHVybiBjb25maWdcbiAgfVxuXG4gIF9tZXJnZUNvbmZpZ09iaihjb25maWcsIGVsZW1lbnQpIHtcbiAgICBjb25zdCBqc29uQ29uZmlnID0gaXNFbGVtZW50KGVsZW1lbnQpID8gTWFuaXB1bGF0b3IuZ2V0RGF0YUF0dHJpYnV0ZShlbGVtZW50LCAnY29uZmlnJykgOiB7fSAvLyB0cnkgdG8gcGFyc2VcblxuICAgIHJldHVybiB7XG4gICAgICAuLi50aGlzLmNvbnN0cnVjdG9yLkRlZmF1bHQsXG4gICAgICAuLi4odHlwZW9mIGpzb25Db25maWcgPT09ICdvYmplY3QnID8ganNvbkNvbmZpZyA6IHt9KSxcbiAgICAgIC4uLihpc0VsZW1lbnQoZWxlbWVudCkgPyBNYW5pcHVsYXRvci5nZXREYXRhQXR0cmlidXRlcyhlbGVtZW50KSA6IHt9KSxcbiAgICAgIC4uLih0eXBlb2YgY29uZmlnID09PSAnb2JqZWN0JyA/IGNvbmZpZyA6IHt9KVxuICAgIH1cbiAgfVxuXG4gIF90eXBlQ2hlY2tDb25maWcoY29uZmlnLCBjb25maWdUeXBlcyA9IHRoaXMuY29uc3RydWN0b3IuRGVmYXVsdFR5cGUpIHtcbiAgICBmb3IgKGNvbnN0IFtwcm9wZXJ0eSwgZXhwZWN0ZWRUeXBlc10gb2YgT2JqZWN0LmVudHJpZXMoY29uZmlnVHlwZXMpKSB7XG4gICAgICBjb25zdCB2YWx1ZSA9IGNvbmZpZ1twcm9wZXJ0eV1cbiAgICAgIGNvbnN0IHZhbHVlVHlwZSA9IGlzRWxlbWVudCh2YWx1ZSkgPyAnZWxlbWVudCcgOiB0b1R5cGUodmFsdWUpXG5cbiAgICAgIGlmICghbmV3IFJlZ0V4cChleHBlY3RlZFR5cGVzKS50ZXN0KHZhbHVlVHlwZSkpIHtcbiAgICAgICAgdGhyb3cgbmV3IFR5cGVFcnJvcihcbiAgICAgICAgICBgJHt0aGlzLmNvbnN0cnVjdG9yLk5BTUUudG9VcHBlckNhc2UoKX06IE9wdGlvbiBcIiR7cHJvcGVydHl9XCIgcHJvdmlkZWQgdHlwZSBcIiR7dmFsdWVUeXBlfVwiIGJ1dCBleHBlY3RlZCB0eXBlIFwiJHtleHBlY3RlZFR5cGVzfVwiLmBcbiAgICAgICAgKVxuICAgICAgfVxuICAgIH1cbiAgfVxufVxuXG5leHBvcnQgZGVmYXVsdCBDb25maWdcbiIsICIvKipcbiAqIC0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tXG4gKiBCb290c3RyYXAgYmFzZS1jb21wb25lbnQuanNcbiAqIExpY2Vuc2VkIHVuZGVyIE1JVCAoaHR0cHM6Ly9naXRodWIuY29tL3R3YnMvYm9vdHN0cmFwL2Jsb2IvbWFpbi9MSUNFTlNFKVxuICogLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS1cbiAqL1xuXG5pbXBvcnQgRGF0YSBmcm9tICcuL2RvbS9kYXRhLmpzJ1xuaW1wb3J0IEV2ZW50SGFuZGxlciBmcm9tICcuL2RvbS9ldmVudC1oYW5kbGVyLmpzJ1xuaW1wb3J0IENvbmZpZyBmcm9tICcuL3V0aWwvY29uZmlnLmpzJ1xuaW1wb3J0IHsgZXhlY3V0ZUFmdGVyVHJhbnNpdGlvbiwgZ2V0RWxlbWVudCB9IGZyb20gJy4vdXRpbC9pbmRleC5qcydcblxuLyoqXG4gKiBDb25zdGFudHNcbiAqL1xuXG5jb25zdCBWRVJTSU9OID0gJzUuMy4zJ1xuXG4vKipcbiAqIENsYXNzIGRlZmluaXRpb25cbiAqL1xuXG5jbGFzcyBCYXNlQ29tcG9uZW50IGV4dGVuZHMgQ29uZmlnIHtcbiAgY29uc3RydWN0b3IoZWxlbWVudCwgY29uZmlnKSB7XG4gICAgc3VwZXIoKVxuXG4gICAgZWxlbWVudCA9IGdldEVsZW1lbnQoZWxlbWVudClcbiAgICBpZiAoIWVsZW1lbnQpIHtcbiAgICAgIHJldHVyblxuICAgIH1cblxuICAgIHRoaXMuX2VsZW1lbnQgPSBlbGVtZW50XG4gICAgdGhpcy5fY29uZmlnID0gdGhpcy5fZ2V0Q29uZmlnKGNvbmZpZylcblxuICAgIERhdGEuc2V0KHRoaXMuX2VsZW1lbnQsIHRoaXMuY29uc3RydWN0b3IuREFUQV9LRVksIHRoaXMpXG4gIH1cblxuICAvLyBQdWJsaWNcbiAgZGlzcG9zZSgpIHtcbiAgICBEYXRhLnJlbW92ZSh0aGlzLl9lbGVtZW50LCB0aGlzLmNvbnN0cnVjdG9yLkRBVEFfS0VZKVxuICAgIEV2ZW50SGFuZGxlci5vZmYodGhpcy5fZWxlbWVudCwgdGhpcy5jb25zdHJ1Y3Rvci5FVkVOVF9LRVkpXG5cbiAgICBmb3IgKGNvbnN0IHByb3BlcnR5TmFtZSBvZiBPYmplY3QuZ2V0T3duUHJvcGVydHlOYW1lcyh0aGlzKSkge1xuICAgICAgdGhpc1twcm9wZXJ0eU5hbWVdID0gbnVsbFxuICAgIH1cbiAgfVxuXG4gIF9xdWV1ZUNhbGxiYWNrKGNhbGxiYWNrLCBlbGVtZW50LCBpc0FuaW1hdGVkID0gdHJ1ZSkge1xuICAgIGV4ZWN1dGVBZnRlclRyYW5zaXRpb24oY2FsbGJhY2ssIGVsZW1lbnQsIGlzQW5pbWF0ZWQpXG4gIH1cblxuICBfZ2V0Q29uZmlnKGNvbmZpZykge1xuICAgIGNvbmZpZyA9IHRoaXMuX21lcmdlQ29uZmlnT2JqKGNvbmZpZywgdGhpcy5fZWxlbWVudClcbiAgICBjb25maWcgPSB0aGlzLl9jb25maWdBZnRlck1lcmdlKGNvbmZpZylcbiAgICB0aGlzLl90eXBlQ2hlY2tDb25maWcoY29uZmlnKVxuICAgIHJldHVybiBjb25maWdcbiAgfVxuXG4gIC8vIFN0YXRpY1xuICBzdGF0aWMgZ2V0SW5zdGFuY2UoZWxlbWVudCkge1xuICAgIHJldHVybiBEYXRhLmdldChnZXRFbGVtZW50KGVsZW1lbnQpLCB0aGlzLkRBVEFfS0VZKVxuICB9XG5cbiAgc3RhdGljIGdldE9yQ3JlYXRlSW5zdGFuY2UoZWxlbWVudCwgY29uZmlnID0ge30pIHtcbiAgICByZXR1cm4gdGhpcy5nZXRJbnN0YW5jZShlbGVtZW50KSB8fCBuZXcgdGhpcyhlbGVtZW50LCB0eXBlb2YgY29uZmlnID09PSAnb2JqZWN0JyA/IGNvbmZpZyA6IG51bGwpXG4gIH1cblxuICBzdGF0aWMgZ2V0IFZFUlNJT04oKSB7XG4gICAgcmV0dXJuIFZFUlNJT05cbiAgfVxuXG4gIHN0YXRpYyBnZXQgREFUQV9LRVkoKSB7XG4gICAgcmV0dXJuIGBicy4ke3RoaXMuTkFNRX1gXG4gIH1cblxuICBzdGF0aWMgZ2V0IEVWRU5UX0tFWSgpIHtcbiAgICByZXR1cm4gYC4ke3RoaXMuREFUQV9LRVl9YFxuICB9XG5cbiAgc3RhdGljIGV2ZW50TmFtZShuYW1lKSB7XG4gICAgcmV0dXJuIGAke25hbWV9JHt0aGlzLkVWRU5UX0tFWX1gXG4gIH1cbn1cblxuZXhwb3J0IGRlZmF1bHQgQmFzZUNvbXBvbmVudFxuIiwgIi8qKlxuICogLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS1cbiAqIEJvb3RzdHJhcCBkb20vc2VsZWN0b3ItZW5naW5lLmpzXG4gKiBMaWNlbnNlZCB1bmRlciBNSVQgKGh0dHBzOi8vZ2l0aHViLmNvbS90d2JzL2Jvb3RzdHJhcC9ibG9iL21haW4vTElDRU5TRSlcbiAqIC0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tXG4gKi9cblxuaW1wb3J0IHsgaXNEaXNhYmxlZCwgaXNWaXNpYmxlLCBwYXJzZVNlbGVjdG9yIH0gZnJvbSAnLi4vdXRpbC9pbmRleC5qcydcblxuY29uc3QgZ2V0U2VsZWN0b3IgPSBlbGVtZW50ID0+IHtcbiAgbGV0IHNlbGVjdG9yID0gZWxlbWVudC5nZXRBdHRyaWJ1dGUoJ2RhdGEtYnMtdGFyZ2V0JylcblxuICBpZiAoIXNlbGVjdG9yIHx8IHNlbGVjdG9yID09PSAnIycpIHtcbiAgICBsZXQgaHJlZkF0dHJpYnV0ZSA9IGVsZW1lbnQuZ2V0QXR0cmlidXRlKCdocmVmJylcblxuICAgIC8vIFRoZSBvbmx5IHZhbGlkIGNvbnRlbnQgdGhhdCBjb3VsZCBkb3VibGUgYXMgYSBzZWxlY3RvciBhcmUgSURzIG9yIGNsYXNzZXMsXG4gICAgLy8gc28gZXZlcnl0aGluZyBzdGFydGluZyB3aXRoIGAjYCBvciBgLmAuIElmIGEgXCJyZWFsXCIgVVJMIGlzIHVzZWQgYXMgdGhlIHNlbGVjdG9yLFxuICAgIC8vIGBkb2N1bWVudC5xdWVyeVNlbGVjdG9yYCB3aWxsIHJpZ2h0ZnVsbHkgY29tcGxhaW4gaXQgaXMgaW52YWxpZC5cbiAgICAvLyBTZWUgaHR0cHM6Ly9naXRodWIuY29tL3R3YnMvYm9vdHN0cmFwL2lzc3Vlcy8zMjI3M1xuICAgIGlmICghaHJlZkF0dHJpYnV0ZSB8fCAoIWhyZWZBdHRyaWJ1dGUuaW5jbHVkZXMoJyMnKSAmJiAhaHJlZkF0dHJpYnV0ZS5zdGFydHNXaXRoKCcuJykpKSB7XG4gICAgICByZXR1cm4gbnVsbFxuICAgIH1cblxuICAgIC8vIEp1c3QgaW4gY2FzZSBzb21lIENNUyBwdXRzIG91dCBhIGZ1bGwgVVJMIHdpdGggdGhlIGFuY2hvciBhcHBlbmRlZFxuICAgIGlmIChocmVmQXR0cmlidXRlLmluY2x1ZGVzKCcjJykgJiYgIWhyZWZBdHRyaWJ1dGUuc3RhcnRzV2l0aCgnIycpKSB7XG4gICAgICBocmVmQXR0cmlidXRlID0gYCMke2hyZWZBdHRyaWJ1dGUuc3BsaXQoJyMnKVsxXX1gXG4gICAgfVxuXG4gICAgc2VsZWN0b3IgPSBocmVmQXR0cmlidXRlICYmIGhyZWZBdHRyaWJ1dGUgIT09ICcjJyA/IGhyZWZBdHRyaWJ1dGUudHJpbSgpIDogbnVsbFxuICB9XG5cbiAgcmV0dXJuIHNlbGVjdG9yID8gc2VsZWN0b3Iuc3BsaXQoJywnKS5tYXAoc2VsID0+IHBhcnNlU2VsZWN0b3Ioc2VsKSkuam9pbignLCcpIDogbnVsbFxufVxuXG5jb25zdCBTZWxlY3RvckVuZ2luZSA9IHtcbiAgZmluZChzZWxlY3RvciwgZWxlbWVudCA9IGRvY3VtZW50LmRvY3VtZW50RWxlbWVudCkge1xuICAgIHJldHVybiBbXS5jb25jYXQoLi4uRWxlbWVudC5wcm90b3R5cGUucXVlcnlTZWxlY3RvckFsbC5jYWxsKGVsZW1lbnQsIHNlbGVjdG9yKSlcbiAgfSxcblxuICBmaW5kT25lKHNlbGVjdG9yLCBlbGVtZW50ID0gZG9jdW1lbnQuZG9jdW1lbnRFbGVtZW50KSB7XG4gICAgcmV0dXJuIEVsZW1lbnQucHJvdG90eXBlLnF1ZXJ5U2VsZWN0b3IuY2FsbChlbGVtZW50LCBzZWxlY3RvcilcbiAgfSxcblxuICBjaGlsZHJlbihlbGVtZW50LCBzZWxlY3Rvcikge1xuICAgIHJldHVybiBbXS5jb25jYXQoLi4uZWxlbWVudC5jaGlsZHJlbikuZmlsdGVyKGNoaWxkID0+IGNoaWxkLm1hdGNoZXMoc2VsZWN0b3IpKVxuICB9LFxuXG4gIHBhcmVudHMoZWxlbWVudCwgc2VsZWN0b3IpIHtcbiAgICBjb25zdCBwYXJlbnRzID0gW11cbiAgICBsZXQgYW5jZXN0b3IgPSBlbGVtZW50LnBhcmVudE5vZGUuY2xvc2VzdChzZWxlY3RvcilcblxuICAgIHdoaWxlIChhbmNlc3Rvcikge1xuICAgICAgcGFyZW50cy5wdXNoKGFuY2VzdG9yKVxuICAgICAgYW5jZXN0b3IgPSBhbmNlc3Rvci5wYXJlbnROb2RlLmNsb3Nlc3Qoc2VsZWN0b3IpXG4gICAgfVxuXG4gICAgcmV0dXJuIHBhcmVudHNcbiAgfSxcblxuICBwcmV2KGVsZW1lbnQsIHNlbGVjdG9yKSB7XG4gICAgbGV0IHByZXZpb3VzID0gZWxlbWVudC5wcmV2aW91c0VsZW1lbnRTaWJsaW5nXG5cbiAgICB3aGlsZSAocHJldmlvdXMpIHtcbiAgICAgIGlmIChwcmV2aW91cy5tYXRjaGVzKHNlbGVjdG9yKSkge1xuICAgICAgICByZXR1cm4gW3ByZXZpb3VzXVxuICAgICAgfVxuXG4gICAgICBwcmV2aW91cyA9IHByZXZpb3VzLnByZXZpb3VzRWxlbWVudFNpYmxpbmdcbiAgICB9XG5cbiAgICByZXR1cm4gW11cbiAgfSxcbiAgLy8gVE9ETzogdGhpcyBpcyBub3cgdW51c2VkOyByZW1vdmUgbGF0ZXIgYWxvbmcgd2l0aCBwcmV2KClcbiAgbmV4dChlbGVtZW50LCBzZWxlY3Rvcikge1xuICAgIGxldCBuZXh0ID0gZWxlbWVudC5uZXh0RWxlbWVudFNpYmxpbmdcblxuICAgIHdoaWxlIChuZXh0KSB7XG4gICAgICBpZiAobmV4dC5tYXRjaGVzKHNlbGVjdG9yKSkge1xuICAgICAgICByZXR1cm4gW25leHRdXG4gICAgICB9XG5cbiAgICAgIG5leHQgPSBuZXh0Lm5leHRFbGVtZW50U2libGluZ1xuICAgIH1cblxuICAgIHJldHVybiBbXVxuICB9LFxuXG4gIGZvY3VzYWJsZUNoaWxkcmVuKGVsZW1lbnQpIHtcbiAgICBjb25zdCBmb2N1c2FibGVzID0gW1xuICAgICAgJ2EnLFxuICAgICAgJ2J1dHRvbicsXG4gICAgICAnaW5wdXQnLFxuICAgICAgJ3RleHRhcmVhJyxcbiAgICAgICdzZWxlY3QnLFxuICAgICAgJ2RldGFpbHMnLFxuICAgICAgJ1t0YWJpbmRleF0nLFxuICAgICAgJ1tjb250ZW50ZWRpdGFibGU9XCJ0cnVlXCJdJ1xuICAgIF0ubWFwKHNlbGVjdG9yID0+IGAke3NlbGVjdG9yfTpub3QoW3RhYmluZGV4Xj1cIi1cIl0pYCkuam9pbignLCcpXG5cbiAgICByZXR1cm4gdGhpcy5maW5kKGZvY3VzYWJsZXMsIGVsZW1lbnQpLmZpbHRlcihlbCA9PiAhaXNEaXNhYmxlZChlbCkgJiYgaXNWaXNpYmxlKGVsKSlcbiAgfSxcblxuICBnZXRTZWxlY3RvckZyb21FbGVtZW50KGVsZW1lbnQpIHtcbiAgICBjb25zdCBzZWxlY3RvciA9IGdldFNlbGVjdG9yKGVsZW1lbnQpXG5cbiAgICBpZiAoc2VsZWN0b3IpIHtcbiAgICAgIHJldHVybiBTZWxlY3RvckVuZ2luZS5maW5kT25lKHNlbGVjdG9yKSA/IHNlbGVjdG9yIDogbnVsbFxuICAgIH1cblxuICAgIHJldHVybiBudWxsXG4gIH0sXG5cbiAgZ2V0RWxlbWVudEZyb21TZWxlY3RvcihlbGVtZW50KSB7XG4gICAgY29uc3Qgc2VsZWN0b3IgPSBnZXRTZWxlY3RvcihlbGVtZW50KVxuXG4gICAgcmV0dXJuIHNlbGVjdG9yID8gU2VsZWN0b3JFbmdpbmUuZmluZE9uZShzZWxlY3RvcikgOiBudWxsXG4gIH0sXG5cbiAgZ2V0TXVsdGlwbGVFbGVtZW50c0Zyb21TZWxlY3RvcihlbGVtZW50KSB7XG4gICAgY29uc3Qgc2VsZWN0b3IgPSBnZXRTZWxlY3RvcihlbGVtZW50KVxuXG4gICAgcmV0dXJuIHNlbGVjdG9yID8gU2VsZWN0b3JFbmdpbmUuZmluZChzZWxlY3RvcikgOiBbXVxuICB9XG59XG5cbmV4cG9ydCBkZWZhdWx0IFNlbGVjdG9yRW5naW5lXG4iLCAiLyoqXG4gKiAtLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLVxuICogQm9vdHN0cmFwIHRhYi5qc1xuICogTGljZW5zZWQgdW5kZXIgTUlUIChodHRwczovL2dpdGh1Yi5jb20vdHdicy9ib290c3RyYXAvYmxvYi9tYWluL0xJQ0VOU0UpXG4gKiAtLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLVxuICovXG5cbmltcG9ydCBCYXNlQ29tcG9uZW50IGZyb20gJy4vYmFzZS1jb21wb25lbnQuanMnXG5pbXBvcnQgRXZlbnRIYW5kbGVyIGZyb20gJy4vZG9tL2V2ZW50LWhhbmRsZXIuanMnXG5pbXBvcnQgU2VsZWN0b3JFbmdpbmUgZnJvbSAnLi9kb20vc2VsZWN0b3ItZW5naW5lLmpzJ1xuaW1wb3J0IHsgZGVmaW5lSlF1ZXJ5UGx1Z2luLCBnZXROZXh0QWN0aXZlRWxlbWVudCwgaXNEaXNhYmxlZCB9IGZyb20gJy4vdXRpbC9pbmRleC5qcydcblxuLyoqXG4gKiBDb25zdGFudHNcbiAqL1xuXG5jb25zdCBOQU1FID0gJ3RhYidcbmNvbnN0IERBVEFfS0VZID0gJ2JzLnRhYidcbmNvbnN0IEVWRU5UX0tFWSA9IGAuJHtEQVRBX0tFWX1gXG5cbmNvbnN0IEVWRU5UX0hJREUgPSBgaGlkZSR7RVZFTlRfS0VZfWBcbmNvbnN0IEVWRU5UX0hJRERFTiA9IGBoaWRkZW4ke0VWRU5UX0tFWX1gXG5jb25zdCBFVkVOVF9TSE9XID0gYHNob3cke0VWRU5UX0tFWX1gXG5jb25zdCBFVkVOVF9TSE9XTiA9IGBzaG93biR7RVZFTlRfS0VZfWBcbmNvbnN0IEVWRU5UX0NMSUNLX0RBVEFfQVBJID0gYGNsaWNrJHtFVkVOVF9LRVl9YFxuY29uc3QgRVZFTlRfS0VZRE9XTiA9IGBrZXlkb3duJHtFVkVOVF9LRVl9YFxuY29uc3QgRVZFTlRfTE9BRF9EQVRBX0FQSSA9IGBsb2FkJHtFVkVOVF9LRVl9YFxuXG5jb25zdCBBUlJPV19MRUZUX0tFWSA9ICdBcnJvd0xlZnQnXG5jb25zdCBBUlJPV19SSUdIVF9LRVkgPSAnQXJyb3dSaWdodCdcbmNvbnN0IEFSUk9XX1VQX0tFWSA9ICdBcnJvd1VwJ1xuY29uc3QgQVJST1dfRE9XTl9LRVkgPSAnQXJyb3dEb3duJ1xuY29uc3QgSE9NRV9LRVkgPSAnSG9tZSdcbmNvbnN0IEVORF9LRVkgPSAnRW5kJ1xuXG5jb25zdCBDTEFTU19OQU1FX0FDVElWRSA9ICdhY3RpdmUnXG5jb25zdCBDTEFTU19OQU1FX0ZBREUgPSAnZmFkZSdcbmNvbnN0IENMQVNTX05BTUVfU0hPVyA9ICdzaG93J1xuY29uc3QgQ0xBU1NfRFJPUERPV04gPSAnZHJvcGRvd24nXG5cbmNvbnN0IFNFTEVDVE9SX0RST1BET1dOX1RPR0dMRSA9ICcuZHJvcGRvd24tdG9nZ2xlJ1xuY29uc3QgU0VMRUNUT1JfRFJPUERPV05fTUVOVSA9ICcuZHJvcGRvd24tbWVudSdcbmNvbnN0IE5PVF9TRUxFQ1RPUl9EUk9QRE9XTl9UT0dHTEUgPSBgOm5vdCgke1NFTEVDVE9SX0RST1BET1dOX1RPR0dMRX0pYFxuXG5jb25zdCBTRUxFQ1RPUl9UQUJfUEFORUwgPSAnLmxpc3QtZ3JvdXAsIC5uYXYsIFtyb2xlPVwidGFibGlzdFwiXSdcbmNvbnN0IFNFTEVDVE9SX09VVEVSID0gJy5uYXYtaXRlbSwgLmxpc3QtZ3JvdXAtaXRlbSdcbmNvbnN0IFNFTEVDVE9SX0lOTkVSID0gYC5uYXYtbGluayR7Tk9UX1NFTEVDVE9SX0RST1BET1dOX1RPR0dMRX0sIC5saXN0LWdyb3VwLWl0ZW0ke05PVF9TRUxFQ1RPUl9EUk9QRE9XTl9UT0dHTEV9LCBbcm9sZT1cInRhYlwiXSR7Tk9UX1NFTEVDVE9SX0RST1BET1dOX1RPR0dMRX1gXG5jb25zdCBTRUxFQ1RPUl9EQVRBX1RPR0dMRSA9ICdbZGF0YS1icy10b2dnbGU9XCJ0YWJcIl0sIFtkYXRhLWJzLXRvZ2dsZT1cInBpbGxcIl0sIFtkYXRhLWJzLXRvZ2dsZT1cImxpc3RcIl0nIC8vIFRPRE86IGNvdWxkIG9ubHkgYmUgYHRhYmAgaW4gdjZcbmNvbnN0IFNFTEVDVE9SX0lOTkVSX0VMRU0gPSBgJHtTRUxFQ1RPUl9JTk5FUn0sICR7U0VMRUNUT1JfREFUQV9UT0dHTEV9YFxuXG5jb25zdCBTRUxFQ1RPUl9EQVRBX1RPR0dMRV9BQ1RJVkUgPSBgLiR7Q0xBU1NfTkFNRV9BQ1RJVkV9W2RhdGEtYnMtdG9nZ2xlPVwidGFiXCJdLCAuJHtDTEFTU19OQU1FX0FDVElWRX1bZGF0YS1icy10b2dnbGU9XCJwaWxsXCJdLCAuJHtDTEFTU19OQU1FX0FDVElWRX1bZGF0YS1icy10b2dnbGU9XCJsaXN0XCJdYFxuXG4vKipcbiAqIENsYXNzIGRlZmluaXRpb25cbiAqL1xuXG5jbGFzcyBUYWIgZXh0ZW5kcyBCYXNlQ29tcG9uZW50IHtcbiAgY29uc3RydWN0b3IoZWxlbWVudCkge1xuICAgIHN1cGVyKGVsZW1lbnQpXG4gICAgdGhpcy5fcGFyZW50ID0gdGhpcy5fZWxlbWVudC5jbG9zZXN0KFNFTEVDVE9SX1RBQl9QQU5FTClcblxuICAgIGlmICghdGhpcy5fcGFyZW50KSB7XG4gICAgICByZXR1cm5cbiAgICAgIC8vIFRPRE86IHNob3VsZCB0aHJvdyBleGNlcHRpb24gaW4gdjZcbiAgICAgIC8vIHRocm93IG5ldyBUeXBlRXJyb3IoYCR7ZWxlbWVudC5vdXRlckhUTUx9IGhhcyBub3QgYSB2YWxpZCBwYXJlbnQgJHtTRUxFQ1RPUl9JTk5FUl9FTEVNfWApXG4gICAgfVxuXG4gICAgLy8gU2V0IHVwIGluaXRpYWwgYXJpYSBhdHRyaWJ1dGVzXG4gICAgdGhpcy5fc2V0SW5pdGlhbEF0dHJpYnV0ZXModGhpcy5fcGFyZW50LCB0aGlzLl9nZXRDaGlsZHJlbigpKVxuXG4gICAgRXZlbnRIYW5kbGVyLm9uKHRoaXMuX2VsZW1lbnQsIEVWRU5UX0tFWURPV04sIGV2ZW50ID0+IHRoaXMuX2tleWRvd24oZXZlbnQpKVxuICB9XG5cbiAgLy8gR2V0dGVyc1xuICBzdGF0aWMgZ2V0IE5BTUUoKSB7XG4gICAgcmV0dXJuIE5BTUVcbiAgfVxuXG4gIC8vIFB1YmxpY1xuICBzaG93KCkgeyAvLyBTaG93cyB0aGlzIGVsZW0gYW5kIGRlYWN0aXZhdGUgdGhlIGFjdGl2ZSBzaWJsaW5nIGlmIGV4aXN0c1xuICAgIGNvbnN0IGlubmVyRWxlbSA9IHRoaXMuX2VsZW1lbnRcbiAgICBpZiAodGhpcy5fZWxlbUlzQWN0aXZlKGlubmVyRWxlbSkpIHtcbiAgICAgIHJldHVyblxuICAgIH1cblxuICAgIC8vIFNlYXJjaCBmb3IgYWN0aXZlIHRhYiBvbiBzYW1lIHBhcmVudCB0byBkZWFjdGl2YXRlIGl0XG4gICAgY29uc3QgYWN0aXZlID0gdGhpcy5fZ2V0QWN0aXZlRWxlbSgpXG5cbiAgICBjb25zdCBoaWRlRXZlbnQgPSBhY3RpdmUgP1xuICAgICAgRXZlbnRIYW5kbGVyLnRyaWdnZXIoYWN0aXZlLCBFVkVOVF9ISURFLCB7IHJlbGF0ZWRUYXJnZXQ6IGlubmVyRWxlbSB9KSA6XG4gICAgICBudWxsXG5cbiAgICBjb25zdCBzaG93RXZlbnQgPSBFdmVudEhhbmRsZXIudHJpZ2dlcihpbm5lckVsZW0sIEVWRU5UX1NIT1csIHsgcmVsYXRlZFRhcmdldDogYWN0aXZlIH0pXG5cbiAgICBpZiAoc2hvd0V2ZW50LmRlZmF1bHRQcmV2ZW50ZWQgfHwgKGhpZGVFdmVudCAmJiBoaWRlRXZlbnQuZGVmYXVsdFByZXZlbnRlZCkpIHtcbiAgICAgIHJldHVyblxuICAgIH1cblxuICAgIHRoaXMuX2RlYWN0aXZhdGUoYWN0aXZlLCBpbm5lckVsZW0pXG4gICAgdGhpcy5fYWN0aXZhdGUoaW5uZXJFbGVtLCBhY3RpdmUpXG4gIH1cblxuICAvLyBQcml2YXRlXG4gIF9hY3RpdmF0ZShlbGVtZW50LCByZWxhdGVkRWxlbSkge1xuICAgIGlmICghZWxlbWVudCkge1xuICAgICAgcmV0dXJuXG4gICAgfVxuXG4gICAgZWxlbWVudC5jbGFzc0xpc3QuYWRkKENMQVNTX05BTUVfQUNUSVZFKVxuXG4gICAgdGhpcy5fYWN0aXZhdGUoU2VsZWN0b3JFbmdpbmUuZ2V0RWxlbWVudEZyb21TZWxlY3RvcihlbGVtZW50KSkgLy8gU2VhcmNoIGFuZCBhY3RpdmF0ZS9zaG93IHRoZSBwcm9wZXIgc2VjdGlvblxuXG4gICAgY29uc3QgY29tcGxldGUgPSAoKSA9PiB7XG4gICAgICBpZiAoZWxlbWVudC5nZXRBdHRyaWJ1dGUoJ3JvbGUnKSAhPT0gJ3RhYicpIHtcbiAgICAgICAgZWxlbWVudC5jbGFzc0xpc3QuYWRkKENMQVNTX05BTUVfU0hPVylcbiAgICAgICAgcmV0dXJuXG4gICAgICB9XG5cbiAgICAgIGVsZW1lbnQucmVtb3ZlQXR0cmlidXRlKCd0YWJpbmRleCcpXG4gICAgICBlbGVtZW50LnNldEF0dHJpYnV0ZSgnYXJpYS1zZWxlY3RlZCcsIHRydWUpXG4gICAgICB0aGlzLl90b2dnbGVEcm9wRG93bihlbGVtZW50LCB0cnVlKVxuICAgICAgRXZlbnRIYW5kbGVyLnRyaWdnZXIoZWxlbWVudCwgRVZFTlRfU0hPV04sIHtcbiAgICAgICAgcmVsYXRlZFRhcmdldDogcmVsYXRlZEVsZW1cbiAgICAgIH0pXG4gICAgfVxuXG4gICAgdGhpcy5fcXVldWVDYWxsYmFjayhjb21wbGV0ZSwgZWxlbWVudCwgZWxlbWVudC5jbGFzc0xpc3QuY29udGFpbnMoQ0xBU1NfTkFNRV9GQURFKSlcbiAgfVxuXG4gIF9kZWFjdGl2YXRlKGVsZW1lbnQsIHJlbGF0ZWRFbGVtKSB7XG4gICAgaWYgKCFlbGVtZW50KSB7XG4gICAgICByZXR1cm5cbiAgICB9XG5cbiAgICBlbGVtZW50LmNsYXNzTGlzdC5yZW1vdmUoQ0xBU1NfTkFNRV9BQ1RJVkUpXG4gICAgZWxlbWVudC5ibHVyKClcblxuICAgIHRoaXMuX2RlYWN0aXZhdGUoU2VsZWN0b3JFbmdpbmUuZ2V0RWxlbWVudEZyb21TZWxlY3RvcihlbGVtZW50KSkgLy8gU2VhcmNoIGFuZCBkZWFjdGl2YXRlIHRoZSBzaG93biBzZWN0aW9uIHRvb1xuXG4gICAgY29uc3QgY29tcGxldGUgPSAoKSA9PiB7XG4gICAgICBpZiAoZWxlbWVudC5nZXRBdHRyaWJ1dGUoJ3JvbGUnKSAhPT0gJ3RhYicpIHtcbiAgICAgICAgZWxlbWVudC5jbGFzc0xpc3QucmVtb3ZlKENMQVNTX05BTUVfU0hPVylcbiAgICAgICAgcmV0dXJuXG4gICAgICB9XG5cbiAgICAgIGVsZW1lbnQuc2V0QXR0cmlidXRlKCdhcmlhLXNlbGVjdGVkJywgZmFsc2UpXG4gICAgICBlbGVtZW50LnNldEF0dHJpYnV0ZSgndGFiaW5kZXgnLCAnLTEnKVxuICAgICAgdGhpcy5fdG9nZ2xlRHJvcERvd24oZWxlbWVudCwgZmFsc2UpXG4gICAgICBFdmVudEhhbmRsZXIudHJpZ2dlcihlbGVtZW50LCBFVkVOVF9ISURERU4sIHsgcmVsYXRlZFRhcmdldDogcmVsYXRlZEVsZW0gfSlcbiAgICB9XG5cbiAgICB0aGlzLl9xdWV1ZUNhbGxiYWNrKGNvbXBsZXRlLCBlbGVtZW50LCBlbGVtZW50LmNsYXNzTGlzdC5jb250YWlucyhDTEFTU19OQU1FX0ZBREUpKVxuICB9XG5cbiAgX2tleWRvd24oZXZlbnQpIHtcbiAgICBpZiAoIShbQVJST1dfTEVGVF9LRVksIEFSUk9XX1JJR0hUX0tFWSwgQVJST1dfVVBfS0VZLCBBUlJPV19ET1dOX0tFWSwgSE9NRV9LRVksIEVORF9LRVldLmluY2x1ZGVzKGV2ZW50LmtleSkpKSB7XG4gICAgICByZXR1cm5cbiAgICB9XG5cbiAgICBldmVudC5zdG9wUHJvcGFnYXRpb24oKS8vIHN0b3BQcm9wYWdhdGlvbi9wcmV2ZW50RGVmYXVsdCBib3RoIGFkZGVkIHRvIHN1cHBvcnQgdXAvZG93biBrZXlzIHdpdGhvdXQgc2Nyb2xsaW5nIHRoZSBwYWdlXG4gICAgZXZlbnQucHJldmVudERlZmF1bHQoKVxuXG4gICAgY29uc3QgY2hpbGRyZW4gPSB0aGlzLl9nZXRDaGlsZHJlbigpLmZpbHRlcihlbGVtZW50ID0+ICFpc0Rpc2FibGVkKGVsZW1lbnQpKVxuICAgIGxldCBuZXh0QWN0aXZlRWxlbWVudFxuXG4gICAgaWYgKFtIT01FX0tFWSwgRU5EX0tFWV0uaW5jbHVkZXMoZXZlbnQua2V5KSkge1xuICAgICAgbmV4dEFjdGl2ZUVsZW1lbnQgPSBjaGlsZHJlbltldmVudC5rZXkgPT09IEhPTUVfS0VZID8gMCA6IGNoaWxkcmVuLmxlbmd0aCAtIDFdXG4gICAgfSBlbHNlIHtcbiAgICAgIGNvbnN0IGlzTmV4dCA9IFtBUlJPV19SSUdIVF9LRVksIEFSUk9XX0RPV05fS0VZXS5pbmNsdWRlcyhldmVudC5rZXkpXG4gICAgICBuZXh0QWN0aXZlRWxlbWVudCA9IGdldE5leHRBY3RpdmVFbGVtZW50KGNoaWxkcmVuLCBldmVudC50YXJnZXQsIGlzTmV4dCwgdHJ1ZSlcbiAgICB9XG5cbiAgICBpZiAobmV4dEFjdGl2ZUVsZW1lbnQpIHtcbiAgICAgIG5leHRBY3RpdmVFbGVtZW50LmZvY3VzKHsgcHJldmVudFNjcm9sbDogdHJ1ZSB9KVxuICAgICAgVGFiLmdldE9yQ3JlYXRlSW5zdGFuY2UobmV4dEFjdGl2ZUVsZW1lbnQpLnNob3coKVxuICAgIH1cbiAgfVxuXG4gIF9nZXRDaGlsZHJlbigpIHsgLy8gY29sbGVjdGlvbiBvZiBpbm5lciBlbGVtZW50c1xuICAgIHJldHVybiBTZWxlY3RvckVuZ2luZS5maW5kKFNFTEVDVE9SX0lOTkVSX0VMRU0sIHRoaXMuX3BhcmVudClcbiAgfVxuXG4gIF9nZXRBY3RpdmVFbGVtKCkge1xuICAgIHJldHVybiB0aGlzLl9nZXRDaGlsZHJlbigpLmZpbmQoY2hpbGQgPT4gdGhpcy5fZWxlbUlzQWN0aXZlKGNoaWxkKSkgfHwgbnVsbFxuICB9XG5cbiAgX3NldEluaXRpYWxBdHRyaWJ1dGVzKHBhcmVudCwgY2hpbGRyZW4pIHtcbiAgICB0aGlzLl9zZXRBdHRyaWJ1dGVJZk5vdEV4aXN0cyhwYXJlbnQsICdyb2xlJywgJ3RhYmxpc3QnKVxuXG4gICAgZm9yIChjb25zdCBjaGlsZCBvZiBjaGlsZHJlbikge1xuICAgICAgdGhpcy5fc2V0SW5pdGlhbEF0dHJpYnV0ZXNPbkNoaWxkKGNoaWxkKVxuICAgIH1cbiAgfVxuXG4gIF9zZXRJbml0aWFsQXR0cmlidXRlc09uQ2hpbGQoY2hpbGQpIHtcbiAgICBjaGlsZCA9IHRoaXMuX2dldElubmVyRWxlbWVudChjaGlsZClcbiAgICBjb25zdCBpc0FjdGl2ZSA9IHRoaXMuX2VsZW1Jc0FjdGl2ZShjaGlsZClcbiAgICBjb25zdCBvdXRlckVsZW0gPSB0aGlzLl9nZXRPdXRlckVsZW1lbnQoY2hpbGQpXG4gICAgY2hpbGQuc2V0QXR0cmlidXRlKCdhcmlhLXNlbGVjdGVkJywgaXNBY3RpdmUpXG5cbiAgICBpZiAob3V0ZXJFbGVtICE9PSBjaGlsZCkge1xuICAgICAgdGhpcy5fc2V0QXR0cmlidXRlSWZOb3RFeGlzdHMob3V0ZXJFbGVtLCAncm9sZScsICdwcmVzZW50YXRpb24nKVxuICAgIH1cblxuICAgIGlmICghaXNBY3RpdmUpIHtcbiAgICAgIGNoaWxkLnNldEF0dHJpYnV0ZSgndGFiaW5kZXgnLCAnLTEnKVxuICAgIH1cblxuICAgIHRoaXMuX3NldEF0dHJpYnV0ZUlmTm90RXhpc3RzKGNoaWxkLCAncm9sZScsICd0YWInKVxuXG4gICAgLy8gc2V0IGF0dHJpYnV0ZXMgdG8gdGhlIHJlbGF0ZWQgcGFuZWwgdG9vXG4gICAgdGhpcy5fc2V0SW5pdGlhbEF0dHJpYnV0ZXNPblRhcmdldFBhbmVsKGNoaWxkKVxuICB9XG5cbiAgX3NldEluaXRpYWxBdHRyaWJ1dGVzT25UYXJnZXRQYW5lbChjaGlsZCkge1xuICAgIGNvbnN0IHRhcmdldCA9IFNlbGVjdG9yRW5naW5lLmdldEVsZW1lbnRGcm9tU2VsZWN0b3IoY2hpbGQpXG5cbiAgICBpZiAoIXRhcmdldCkge1xuICAgICAgcmV0dXJuXG4gICAgfVxuXG4gICAgdGhpcy5fc2V0QXR0cmlidXRlSWZOb3RFeGlzdHModGFyZ2V0LCAncm9sZScsICd0YWJwYW5lbCcpXG5cbiAgICBpZiAoY2hpbGQuaWQpIHtcbiAgICAgIHRoaXMuX3NldEF0dHJpYnV0ZUlmTm90RXhpc3RzKHRhcmdldCwgJ2FyaWEtbGFiZWxsZWRieScsIGAke2NoaWxkLmlkfWApXG4gICAgfVxuICB9XG5cbiAgX3RvZ2dsZURyb3BEb3duKGVsZW1lbnQsIG9wZW4pIHtcbiAgICBjb25zdCBvdXRlckVsZW0gPSB0aGlzLl9nZXRPdXRlckVsZW1lbnQoZWxlbWVudClcbiAgICBpZiAoIW91dGVyRWxlbS5jbGFzc0xpc3QuY29udGFpbnMoQ0xBU1NfRFJPUERPV04pKSB7XG4gICAgICByZXR1cm5cbiAgICB9XG5cbiAgICBjb25zdCB0b2dnbGUgPSAoc2VsZWN0b3IsIGNsYXNzTmFtZSkgPT4ge1xuICAgICAgY29uc3QgZWxlbWVudCA9IFNlbGVjdG9yRW5naW5lLmZpbmRPbmUoc2VsZWN0b3IsIG91dGVyRWxlbSlcbiAgICAgIGlmIChlbGVtZW50KSB7XG4gICAgICAgIGVsZW1lbnQuY2xhc3NMaXN0LnRvZ2dsZShjbGFzc05hbWUsIG9wZW4pXG4gICAgICB9XG4gICAgfVxuXG4gICAgdG9nZ2xlKFNFTEVDVE9SX0RST1BET1dOX1RPR0dMRSwgQ0xBU1NfTkFNRV9BQ1RJVkUpXG4gICAgdG9nZ2xlKFNFTEVDVE9SX0RST1BET1dOX01FTlUsIENMQVNTX05BTUVfU0hPVylcbiAgICBvdXRlckVsZW0uc2V0QXR0cmlidXRlKCdhcmlhLWV4cGFuZGVkJywgb3BlbilcbiAgfVxuXG4gIF9zZXRBdHRyaWJ1dGVJZk5vdEV4aXN0cyhlbGVtZW50LCBhdHRyaWJ1dGUsIHZhbHVlKSB7XG4gICAgaWYgKCFlbGVtZW50Lmhhc0F0dHJpYnV0ZShhdHRyaWJ1dGUpKSB7XG4gICAgICBlbGVtZW50LnNldEF0dHJpYnV0ZShhdHRyaWJ1dGUsIHZhbHVlKVxuICAgIH1cbiAgfVxuXG4gIF9lbGVtSXNBY3RpdmUoZWxlbSkge1xuICAgIHJldHVybiBlbGVtLmNsYXNzTGlzdC5jb250YWlucyhDTEFTU19OQU1FX0FDVElWRSlcbiAgfVxuXG4gIC8vIFRyeSB0byBnZXQgdGhlIGlubmVyIGVsZW1lbnQgKHVzdWFsbHkgdGhlIC5uYXYtbGluaylcbiAgX2dldElubmVyRWxlbWVudChlbGVtKSB7XG4gICAgcmV0dXJuIGVsZW0ubWF0Y2hlcyhTRUxFQ1RPUl9JTk5FUl9FTEVNKSA/IGVsZW0gOiBTZWxlY3RvckVuZ2luZS5maW5kT25lKFNFTEVDVE9SX0lOTkVSX0VMRU0sIGVsZW0pXG4gIH1cblxuICAvLyBUcnkgdG8gZ2V0IHRoZSBvdXRlciBlbGVtZW50ICh1c3VhbGx5IHRoZSAubmF2LWl0ZW0pXG4gIF9nZXRPdXRlckVsZW1lbnQoZWxlbSkge1xuICAgIHJldHVybiBlbGVtLmNsb3Nlc3QoU0VMRUNUT1JfT1VURVIpIHx8IGVsZW1cbiAgfVxuXG4gIC8vIFN0YXRpY1xuICBzdGF0aWMgalF1ZXJ5SW50ZXJmYWNlKGNvbmZpZykge1xuICAgIHJldHVybiB0aGlzLmVhY2goZnVuY3Rpb24gKCkge1xuICAgICAgY29uc3QgZGF0YSA9IFRhYi5nZXRPckNyZWF0ZUluc3RhbmNlKHRoaXMpXG5cbiAgICAgIGlmICh0eXBlb2YgY29uZmlnICE9PSAnc3RyaW5nJykge1xuICAgICAgICByZXR1cm5cbiAgICAgIH1cblxuICAgICAgaWYgKGRhdGFbY29uZmlnXSA9PT0gdW5kZWZpbmVkIHx8IGNvbmZpZy5zdGFydHNXaXRoKCdfJykgfHwgY29uZmlnID09PSAnY29uc3RydWN0b3InKSB7XG4gICAgICAgIHRocm93IG5ldyBUeXBlRXJyb3IoYE5vIG1ldGhvZCBuYW1lZCBcIiR7Y29uZmlnfVwiYClcbiAgICAgIH1cblxuICAgICAgZGF0YVtjb25maWddKClcbiAgICB9KVxuICB9XG59XG5cbi8qKlxuICogRGF0YSBBUEkgaW1wbGVtZW50YXRpb25cbiAqL1xuXG5FdmVudEhhbmRsZXIub24oZG9jdW1lbnQsIEVWRU5UX0NMSUNLX0RBVEFfQVBJLCBTRUxFQ1RPUl9EQVRBX1RPR0dMRSwgZnVuY3Rpb24gKGV2ZW50KSB7XG4gIGlmIChbJ0EnLCAnQVJFQSddLmluY2x1ZGVzKHRoaXMudGFnTmFtZSkpIHtcbiAgICBldmVudC5wcmV2ZW50RGVmYXVsdCgpXG4gIH1cblxuICBpZiAoaXNEaXNhYmxlZCh0aGlzKSkge1xuICAgIHJldHVyblxuICB9XG5cbiAgVGFiLmdldE9yQ3JlYXRlSW5zdGFuY2UodGhpcykuc2hvdygpXG59KVxuXG4vKipcbiAqIEluaXRpYWxpemUgb24gZm9jdXNcbiAqL1xuRXZlbnRIYW5kbGVyLm9uKHdpbmRvdywgRVZFTlRfTE9BRF9EQVRBX0FQSSwgKCkgPT4ge1xuICBmb3IgKGNvbnN0IGVsZW1lbnQgb2YgU2VsZWN0b3JFbmdpbmUuZmluZChTRUxFQ1RPUl9EQVRBX1RPR0dMRV9BQ1RJVkUpKSB7XG4gICAgVGFiLmdldE9yQ3JlYXRlSW5zdGFuY2UoZWxlbWVudClcbiAgfVxufSlcbi8qKlxuICogalF1ZXJ5XG4gKi9cblxuZGVmaW5lSlF1ZXJ5UGx1Z2luKFRhYilcblxuZXhwb3J0IGRlZmF1bHQgVGFiXG4iLCAiLy8gSW1wb3J0IHRoZSBCb290c3RyYXAgY29tcG9uZW50cyB3ZSB3YW50IHRvIHVzZS5cbi8vIFNlZSBodHRwczovL2dpdGh1Yi5jb20vdHdicy9ib290c3RyYXAvYmxvYi9tYWluL2pzL2luZGV4LnVtZC5qc1xuaW1wb3J0IFRhYiBmcm9tIFwiL2pzL2Jvb3RzdHJhcC9zcmMvdGFiXCI7XG5cbmV4cG9ydCBkZWZhdWx0IHtcbiAgICBUYWJcbn0iXSwKICAibWFwcGluZ3MiOiAiOztBQVdBLE1BQU0sYUFBYSxvQkFBSSxJQUFJO0FBRTNCLE1BQU8sZUFBUTtBQUFBLElBQ2IsSUFBSSxTQUFTLEtBQUssVUFBVTtBQUMxQixVQUFJLENBQUMsV0FBVyxJQUFJLE9BQU8sR0FBRztBQUM1QixtQkFBVyxJQUFJLFNBQVMsb0JBQUksSUFBSSxDQUFDO0FBQUEsTUFDbkM7QUFFQSxZQUFNLGNBQWMsV0FBVyxJQUFJLE9BQU87QUFJMUMsVUFBSSxDQUFDLFlBQVksSUFBSSxHQUFHLEtBQUssWUFBWSxTQUFTLEdBQUc7QUFFbkQsZ0JBQVEsTUFBTSwrRUFBK0UsTUFBTSxLQUFLLFlBQVksS0FBSyxDQUFDLEVBQUUsQ0FBQyxDQUFDLEdBQUc7QUFDakk7QUFBQSxNQUNGO0FBRUEsa0JBQVksSUFBSSxLQUFLLFFBQVE7QUFBQSxJQUMvQjtBQUFBLElBRUEsSUFBSSxTQUFTLEtBQUs7QUFDaEIsVUFBSSxXQUFXLElBQUksT0FBTyxHQUFHO0FBQzNCLGVBQU8sV0FBVyxJQUFJLE9BQU8sRUFBRSxJQUFJLEdBQUcsS0FBSztBQUFBLE1BQzdDO0FBRUEsYUFBTztBQUFBLElBQ1Q7QUFBQSxJQUVBLE9BQU8sU0FBUyxLQUFLO0FBQ25CLFVBQUksQ0FBQyxXQUFXLElBQUksT0FBTyxHQUFHO0FBQzVCO0FBQUEsTUFDRjtBQUVBLFlBQU0sY0FBYyxXQUFXLElBQUksT0FBTztBQUUxQyxrQkFBWSxPQUFPLEdBQUc7QUFHdEIsVUFBSSxZQUFZLFNBQVMsR0FBRztBQUMxQixt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
