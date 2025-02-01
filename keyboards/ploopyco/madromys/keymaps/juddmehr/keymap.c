#include QMK_KEYBOARD_H

// Layer Declarations
#define LAYER_NOMINAL 0
#define LAYER_SCREEN_SHOT 1
#define LAYER_PRECISION_DRAG 2


/********************/
/**** TAP DANCES ****/
/********************/

// Declare tap dances
enum {
    TD_BACK_COPY,
    TD_FORWARD_PASTE,
    TD_BOTTOM_RIGHT,
    SOME_OTHER_DANCE
};


/*****     Tap--Hold Functionality     *****/

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }


/*****     Multi-Tap Decisions    *****/

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_QUINT_TAP, // 5 taps (to make sure you want to do this)
    TD_QUINT_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(tap_dance_state_t *state);

void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);


/*****    Tap Dances to include in Layout     *****/

tap_dance_action_t tap_dance_actions[] = {
    [TD_BACK_COPY] = ACTION_TAP_DANCE_TAP_HOLD(LGUI(KC_LBRC), LGUI(KC_C)),
    [TD_FORWARD_PASTE] = ACTION_TAP_DANCE_TAP_HOLD(LGUI(KC_RBRC), LGUI(KC_V)),
    [TD_BOTTOM_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)
};


/*************************/
/**** CUSTOM KEYCODES ****/
/*************************/

// Custom Keycode Declarations
enum custom_keycodes {
    ESC_UNCLICK = SAFE_RANGE,
    COPY_UNCLICK,
    PASTE_UNCLICK,
    BTN2_UNCLICK,
    BTN1_TOGGLE,
    RECORD_SCREEN,
};

// bool for holding left click (used in several places)
bool mouse_held = false;

void toggle_mouse_hold(void) {
    if (mouse_held) {
        unregister_code(KC_BTN1);
        layer_move(LAYER_NOMINAL);
    } else {
        register_code(KC_BTN1);
    }
    mouse_held = !mouse_held;
}


/******************/
/***** LAYOUT *****/
/******************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_NOMINAL] = LAYOUT(
            KC_BTN2,               // TOP LEFT
            TD(TD_BACK_COPY),      // TOP CENTER LEFT
            TD(TD_FORWARD_PASTE),  // TOP CENTER RIGHT
            DRAG_SCROLL,           // TOP RIGHT
            KC_BTN1,               // BOTTOM LEFT
            TD(TD_BOTTOM_RIGHT)    // BOTTOM RIGHT
            ),
    [LAYER_SCREEN_SHOT] = LAYOUT(
            ESC_UNCLICK,           // TOP LEFT
            ESC_UNCLICK,           // TOP CENTER LEFT
            ESC_UNCLICK,           // TOP CENTER RIGHT
            ESC_UNCLICK,           // TOP RIGHT
            BTN1_TOGGLE,           // BOTTOM LEFT
            ESC_UNCLICK            // BOTTOM RIGHT
             ),
    [LAYER_PRECISION_DRAG] = LAYOUT(
            BTN2_UNCLICK,          // TOP LEFT
            COPY_UNCLICK,          // TOP CENTER LEFT
            PASTE_UNCLICK,         // TOP CENTER RIGHT
            DRAG_SCROLL,           // TOP RIGHT
            BTN1_TOGGLE,           // BOTTOM LEFT
            RECORD_SCREEN          // BOTTOM RIGHT
             ),
};


/*****     Tap-Hold Utilities & Custom Keycodes    *****/
/*
Functionality for Tap or Hold.
Specifically for the use cases of:
-  tapping to send cmd+[ (back in browser and finder, etc.) or hold for cmd+c (copy) [TD_BACK_COPY]
-  tapping to send cmd+] (forward in browser and finder, etc.) or hold for cmd+v (paste) [TD_FORWARD_PASTE]

Also contains cases for custom keycodes:
- BTN1_TOGGLE:
    -toggles holding left mouse button (for click and drag help)
- ESC_UNCLICK:
    - releases left mouse button,
    - sends escape,
    - and goes to nominal layer
- BTN2_UNCLICK:
    - releases left mouse button,
    - sends right mouse button,
    - and goes to nominal layer
- COPY_UNCLICK:
    - releases left mouse button,
    - sends cmd+c,
    - and goes to nominal layer
- PASTE_UNCLICK:
    - releases left mouse button,
    - sends cmd+v,
    - and goes to nominal layer
- RECORD_SCREEN:
    - releases left mouse button,
    - sends cmd+shift+5 (record screen command),
    - and goes to nominal layer
*/


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case TD(TD_BACK_COPY):  // Define tap dance keycode
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(TD_FORWARD_PASTE):  // Define tap dance keycode
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case BTN1_TOGGLE:
            if (record->event.pressed) {
                toggle_mouse_hold();
            }
            break;

        case ESC_UNCLICK:
            if (record->event.pressed) {
                tap_code(KC_ESC);       // Send Escape key
                if (mouse_held){
                    unregister_code(KC_BTN1); // Release Left Mouse Click
                    mouse_held = false;
                }
                layer_move(LAYER_NOMINAL);
            }
            break;

        case BTN2_UNCLICK:
            if (record->event.pressed) {
                tap_code(KC_BTN2);       // Send right click key
                if (mouse_held){
                    unregister_code(KC_BTN1); // Release Left Mouse Click
                    mouse_held = false;
                }
                layer_move(LAYER_NOMINAL);
            }
            break;

        case COPY_UNCLICK:
            if (record->event.pressed) {
                 tap_code16(G(KC_C));
                if (mouse_held){
                    unregister_code(KC_BTN1); // Release Left Mouse Click
                    mouse_held = false;
                }
                layer_move(LAYER_NOMINAL);
            }
            break;

        case PASTE_UNCLICK:
            if (record->event.pressed) {
                 tap_code16(G(KC_V));
                if (mouse_held){
                    unregister_code(KC_BTN1); // Release Left Mouse Click
                    mouse_held = false;
                }
                layer_move(LAYER_NOMINAL);
            }
            break;

        case RECORD_SCREEN:
            if (record->event.pressed) {
                if (mouse_held){
                    unregister_code(KC_BTN1); // Release Left Mouse Click
                    mouse_held = false;
                }
                tap_code16(G(S(KC_5)));
                layer_move(LAYER_NOMINAL);
            }
            break;


    }
    return true;
}

/*****     Multi-tap Utilities     *****/
/*
Functionality for different choices based on number of taps.
Specifically for the use cases of:
- Single tap:
    - sends cmd+shift+4 (screen shot)
    - goes to screen shot layer
- Double tap:
    - engages left click (and holds)
    - goes to precision drag layer
- Quintuple (5x) tap:
    - cycles to next DPI setting (10,000 or 1,000)

Currently no functionality for holds so these conditions are commented out.
*/


td_state_t cur_dance(tap_dance_state_t *state);

void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        /*else return TD_SINGLE_HOLD;*/
    } else if (state->count == 2) {
        if (state->interrupted || !state->pressed) return TD_DOUBLE_TAP;
    /*} else if (state->count == 2) {*/
        /*if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;*/
        /*else if (state->pressed) return TD_DOUBLE_HOLD;*/
        /*else return TD_DOUBLE_TAP;*/
    } else if (state->count == 5) {
        if (state->interrupted || !state->pressed) return TD_QUINT_TAP;
        /*else return TD_QUINT_HOLD;*/
    } else return TD_UNKNOWN;

    return TD_UNKNOWN;
}

static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void x_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(G(S(KC_4)));
            layer_on(LAYER_SCREEN_SHOT);
            break;
        /*case TD_SINGLE_HOLD: register_code(KC_Y); break;*/
        case TD_DOUBLE_TAP:
            toggle_mouse_hold();
            layer_on(LAYER_PRECISION_DRAG);
            break;
        /*case TD_DOUBLE_HOLD: register_code(KC_N); break;*/
        /*case TD_DOUBLE_SINGLE_TAP: tap_code(KC_ESC); register_code(KC_ESC); break;*/
        case TD_QUINT_TAP:
            cycle_dpi();
            break;
        /*case TD_QUINT_HOLD: register_code(KC_0); break;*/
        default: break;
    }
}

void x_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_X);
            break;
        /*case TD_SINGLE_HOLD: unregister_code(KC_Y); break;*/
        case TD_DOUBLE_TAP:
            unregister_code(KC_M);
            break;
        /*case TD_DOUBLE_HOLD: unregister_code(KC_N); break;*/
        /*case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_ESC); break;*/
        /*case TD_QUINT_TAP:*/
        /*    unregister_code16(DPI_CONFIG);*/
        /*    break;*/
        /*case TD_QUINT_HOLD: unregister_code(KC_0); break;*/
        default: break;
    }
    xtap_state.state = TD_NONE;
}
