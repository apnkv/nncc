#pragma once

#include <cstdint>
#include <unordered_set>

namespace nncc::input {

struct Modifier {
    enum Enum {
        None = 0,
        LeftAlt = 0x01,
        RightAlt = 0x02,
        LeftCtrl = 0x04,
        RightCtrl = 0x08,
        LeftShift = 0x10,
        RightShift = 0x20,
        LeftMeta = 0x40,
        RightMeta = 0x80,
    };
};

enum class Key {
    None = 0,
    Esc,
    Return,
    Tab,
    Space,
    Backspace,
    Up,
    Down,
    Left,
    Right,
    Insert,
    Delete,
    Home,
    End,
    PageUp,
    PageDown,
    Print,
    Plus,
    Minus,
    LeftBracket,
    RightBracket,
    Semicolon,
    Quote,
    Comma,
    Period,
    Slash,
    Backslash,
    Tilde,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    NumPad0,
    NumPad1,
    NumPad2,
    NumPad3,
    NumPad4,
    NumPad5,
    NumPad6,
    NumPad7,
    NumPad8,
    NumPad9,
    Key0,
    Key1,
    Key2,
    Key3,
    Key4,
    Key5,
    Key6,
    Key7,
    Key8,
    Key9,
    KeyA,
    KeyB,
    KeyC,
    KeyD,
    KeyE,
    KeyF,
    KeyG,
    KeyH,
    KeyI,
    KeyJ,
    KeyK,
    KeyL,
    KeyM,
    KeyN,
    KeyO,
    KeyP,
    KeyQ,
    KeyR,
    KeyS,
    KeyT,
    KeyU,
    KeyV,
    KeyW,
    KeyX,
    KeyY,
    KeyZ,

    GamepadA,
    GamepadB,
    GamepadX,
    GamepadY,
    GamepadThumbL,
    GamepadThumbR,
    GamepadShoulderL,
    GamepadShoulderR,
    GamepadUp,
    GamepadDown,
    GamepadLeft,
    GamepadRight,
    GamepadBack,
    GamepadStart,
    GamepadGuide,

    Count
};

enum class MouseButton {
    Left,
    Middle,
    Right,

    Count,
    None
};

constexpr int MouseButtonAsInt(const MouseButton& button) {
    return static_cast<int>(MouseButton::Count);
}

struct MouseState {
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;

    double scroll_x = 0;
    double scroll_y = 0;

    bool buttons[static_cast<int>(MouseButton::Count)]{};

    [[nodiscard]] uint8_t GetImGuiPressedMouseButtons() const {
        uint8_t pressed_buttons = 0;
        uint8_t current_button_mask = 1;
        for (bool button: buttons) {
            if (button) {
                pressed_buttons |= current_button_mask;
            }
            current_button_mask <<= 1;
        }
        return pressed_buttons;
    }
};

struct KeyState {
    int modifiers;
    std::unordered_set<Key> pressed_keys;
};

}