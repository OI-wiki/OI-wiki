(function() {
    const customDynamicStyle = document.createElement("style");
    // We must put it outside of the head and body, since they are replaced by the instant navigation feature in the Material theme
    document.documentElement.appendChild(customDynamicStyle);

    const TOGGLE_BUTTON_REFERENCE_ELEMENT_NOT_FOUND_WARNING = "[mkdocs-toggle-sidebar-plugin] Reference element for inserting 'toggle_button' not found. This version of the plugin may not be compatible with this version of the theme. Try updating both to the latest version. If that fails, you can open an GitHub issue.";

    const loadBool = (name, default_value) => {
        const value = localStorage.getItem(`TOGGLE_SIDEBAR_${name}`);
        if (value == null) {
            return default_value;
        } else {
            return value == "1";
        }
    }

    const loadNavigationState = () => loadBool("NAVIGATION", true);
    const loadTocState = () => loadBool("TOC", true);

    const saveBool = (name, value) => {
        localStorage.setItem(`TOGGLE_SIDEBAR_${name}`, value ? "1" : "0");
    }

    const toggleVisibility = (toggleNavigation, toggleTOC) => {
        let newNavigation = loadNavigationState();
        let newTOC = loadTocState();
        
        if (toggleNavigation) {
            newNavigation = !newNavigation;
            saveBool("NAVIGATION", newNavigation);
        }
        if (toggleTOC) {
            newTOC = !newTOC;
            saveBool("TOC", newTOC);
        }
        
        _setVisibility(newNavigation, newTOC);
    }

    const _setVisibility = (newNavigation, newTOC) => {
        console.debug(`Setting new visibility: navigation=${newNavigation}, TOC=${newTOC}`);
        // combine this into one operation, so that it is more efficient (for toggling both) and easier to code with dynamic CSS generation
        customDynamicStyle.innerHTML = setCombinedVisibility(newNavigation, newTOC);
    }

    // START OF INCLUDE
    // This gets replaced with the definitions of: 
    // - setCombinedVisibility(showNavigation: bool, showTOC: bool) -> string (dynamic CSS)
    // - registerKeyboardEventHandler() -> void
    const setCombinedVisibility = (showNavigation, showTOC) => {
    // Hide the button when on mobile (and menu us shown as hamburger menu anyways).
    // Uses the 60em threshold that is used for hiding the TOC, search bar, repo info (name + stars), etc

    let style = `
.mkdocs-toggle-sidebar-button {
    cursor: pointer;
    margin-right: 5px;
    margin-left: 1rem;
}

@media screen and (max-width: 60em) {
    .mkdocs-toggle-sidebar-button {
        display: none;
    }
}
`;
// The TOC has a different break point than the navigation.
// It can be seen on the nav.md-nav--secondary:nth-child(1) element (60em)
// If the screen is smaller, it is shown in the navigation section if you click the nested hamburger menu
if (!showTOC) {
    style += `
@media screen and (min-width: 60em) {
    div.md-sidebar.md-sidebar--secondary {
        display: none;
    }
}
`;
        }
        
    // We always have to show the navigation in mobile view, otherwise the hamburger menu is broken
    // In material for mkdocs's blog mode, navigation's class is '.md-sidebar--post', see #9
    // The exact width (76.1875em) is taken from the styling of the 'body > header > nav > a' element, I think
    if (!showNavigation) {
        style += `
@media screen and (min-width: 76.1875em) {
    div.md-sidebar.md-sidebar--primary, div.md-sidebar.md-sidebar--post {
        display: none;
    }
}
`;
    }

    return style;
}

const addToggleButton = (toggleNavigation, toggleTOC) => {
    const toggleBtn = createDefaultToggleButton(toggleNavigation, toggleTOC);
    toggleBtn.classList.add("md-icon");
  
    const titleElement = document.querySelector(".md-header__title");
    if (titleElement) {
        titleElement.parentNode.insertBefore(toggleBtn, titleElement.nextSibling);  
    } else {
        console.warn(TOGGLE_BUTTON_REFERENCE_ELEMENT_NOT_FOUND_WARNING);
    }
}

const registerKeyboardEventHandler = () => {
    // Custom key handlers: SEE https://squidfunk.github.io/mkdocs-material/setup/setting-up-navigation/?h=key+bind#docsjavascriptsshortcutsjs
    keyboard$.subscribe(key => {
        if (key.mode === "global") {
            if (coreEventListenerLogic(key.type)) {
                // event handled, stop propagation
                key.claim();
            }
        }
    });
}

    // END OF INCLUDE

    // argument: string, returns true if the key was handled and the event should be marked as already handled
    const coreEventListenerLogic = (keyChar) => {
        if (keyChar === "t") {
            toggleVisibility(false, true);
            return true;
        } else if (keyChar === "m") {
            toggleVisibility(true, false);
            return true;
        } else if (keyChar === "b") {
            toggleVisibility(true, true);
            return true;
        } else {
            return false;
        }
    }

    const onPageLoadedAction = () => {
        console.log("The mkdocs-toggle-sidebar-plugin is installed. It adds the following key bindings:\n T -> toggle table of contents sidebar\n M -> toggle navigation menu sidebar\n B -> toggle both sidebars (TOC and navigation)");

        const toggle_button = "all";
        if (toggle_button == "none") {
            // do nothing
        } else if (toggle_button == "navigation") {
            addToggleButton(true, false);
        } else if (toggle_button == "toc") {
            addToggleButton(false, true);
        } else if (toggle_button == "all") {
            addToggleButton(true, true);
        } else {
            console.error(`[mkdocs-toggle-sidebar-plugin] Unknown value for toggle_button: '${toggleButtonType}'`);
        }

        registerKeyboardEventHandler();
    }

    const createDefaultToggleButton = (toggleNavigation, toggleTOC) => {
        const toggleBtn = document.createElement("div");
        toggleBtn.className = "mkdocs-toggle-sidebar-button";
        toggleBtn.innerHTML = `<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M3 6h18v2H3V6m0 5h18v2H3v-2m0 5h18v2H3v-2Z"></path></svg>`;
        if (toggleNavigation && toggleTOC) {
            toggleBtn.title = "Toggle Navigation and Table of Contents";
        } else if (toggleNavigation) {
            toggleBtn.title = "Toggle Navigation";
        } else if (toggleTOC) {
            toggleBtn.title = "Toggle Table of Contents";
        }
        toggleBtn.addEventListener("click", () => toggleVisibility(toggleNavigation, toggleTOC));
        return toggleBtn;
    };

    // Export functions that the user can call to modify the state
    window.MkdocsToggleSidebarPlugin = {
        setNavigationVisibility: (show) => {
            saveBool("NAVIGATION", show);
            _setVisibility(show, loadTocState());
        },
        setTocVisibility: (show) => {
            saveBool("TOC", show);
            _setVisibility(loadNavigationState(), show);
        },
        setAllVisibility: (showNavigation, showTOC) => {
            saveBool("NAVIGATION", showNavigation);
            saveBool("TOC", showTOC);
            _setVisibility(showNavigation, showTOC);
        },
        toggleNavigationVisibility: () => toggleVisibility(true, false),
        toggleTocVisibility: () => toggleVisibility(false, true),
        toggleAllVisibility: () => toggleVisibility(true, true)
    };

    // Run this immediately instead of waiting for page.onload to prevent page flicker
    customDynamicStyle.innerHTML = setCombinedVisibility(loadNavigationState(), loadTocState());
    // console.log("Debug: hide sidebar completed");

    // SEE https://developer.mozilla.org/en-US/docs/Web/API/Document/DOMContentLoaded_event#checking_whether_loading_is_already_complete
    if (document.readyState === "loading") {
        // console.debug("Registering DOMContentLoaded event listener");
        document.addEventListener("DOMContentLoaded", onPageLoadedAction);
    } else {
        // console.debug("DOMContentLoaded has already fired");
        onPageLoadedAction();
    }
}());
