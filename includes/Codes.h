#ifndef CODES_H
# define CODES_H

# include "allgl.h"

# define DN_PRESS				GLFW_PRESS
# define DN_REPEAT				GLFW_REPEAT
# define DN_RELEASE				GLFW_RELEASE

# define DN_KEY_UNKNOWN			GLFW_KEY_UNKNOWN
# define DN_KEY_SPACE			GLFW_KEY_SPACE
# define DN_KEY_APPOSTROPHE		GLFW_KEY_APOSTROPHE
# define DN_KEY_COMMA			GLFW_KEY_COMMA
# define DN_KEY_MINUS			GLFW_KEY_MINUS
# define DN_KEY_PERIOD			GLFW_KEY_PERIOD
# define DN_KEY_SLASH			GLFW_KEY_SLASH
# define DN_KEY_0				GLFW_KEY_0
# define DN_KEY_1				GLFW_KEY_1
# define DN_KEY_2				GLFW_KEY_2
# define DN_KEY_3				GLFW_KEY_3
# define DN_KEY_4				GLFW_KEY_4
# define DN_KEY_5				GLFW_KEY_5
# define DN_KEY_6				GLFW_KEY_6
# define DN_KEY_7				GLFW_KEY_7
# define DN_KEY_8				GLFW_KEY_8
# define DN_KEY_9				GLFW_KEY_9
# define DN_KEY_SEMICOLON		GLFW_KEY_SEMICOLON
# define DN_KEY_EQUAL			GLFW_KEY_EQUAL
# define DN_KEY_A				GLFW_KEY_A
# define DN_KEY_B				GLFW_KEY_B
# define DN_KEY_C				GLFW_KEY_C
# define DN_KEY_D				GLFW_KEY_D
# define DN_KEY_E				GLFW_KEY_E
# define DN_KEY_F				GLFW_KEY_F
# define DN_KEY_G				GLFW_KEY_G
# define DN_KEY_H				GLFW_KEY_H
# define DN_KEY_I				GLFW_KEY_I
# define DN_KEY_J				GLFW_KEY_J
# define DN_KEY_K				GLFW_KEY_K
# define DN_KEY_L				GLFW_KEY_L
# define DN_KEY_M				GLFW_KEY_M
# define DN_KEY_N				GLFW_KEY_N
# define DN_KEY_O				GLFW_KEY_O
# define DN_KEY_P				GLFW_KEY_P
# define DN_KEY_Q				GLFW_KEY_Q
# define DN_KEY_R				GLFW_KEY_R
# define DN_KEY_S				GLFW_KEY_S
# define DN_KEY_T				GLFW_KEY_T
# define DN_KEY_U				GLFW_KEY_U
# define DN_KEY_V				GLFW_KEY_V
# define DN_KEY_W				GLFW_KEY_W
# define DN_KEY_X				GLFW_KEY_X
# define DN_KEY_Y				GLFW_KEY_Y
# define DN_KEY_Z				GLFW_KEY_Z
# define DN_KEY_LEFT_BRACKET	GLFW_KEY_LEFT_BRACKET
# define DN_KEY_BACKSLASH		GLFW_KEY_BACKSLASH
# define DN_KEY_RIGHT_BRACKET	GLFW_KEY_RIGHT_BRACKET
# define DN_KEY_GRAVE_ACCENT	GLFW_KEY_GRAVE_ACCENT
# define DN_KEY_WORLD_1			GLFW_KEY_WORLD_1
# define DN_KEY_WORLD_2			GLFW_KEY_WORLD_2
# define DN_KEY_ESCAPE			GLFW_KEY_ESCAPE
# define DN_KEY_ENTER			GLFW_KEY_ENTER
# define DN_KEY_TAB				GLFW_KEY_TAB
# define DN_KEY_BACKSPACE		GLFW_KEY_BACKSPACE
# define DN_KEY_INSERT			GLFW_KEY_INSERT
# define DN_KEY_DELETE			GLFW_KEY_DELETE
# define DN_KEY_RIGHT			GLFW_KEY_RIGHT
# define DN_KEY_LEFT			GLFW_KEY_LEFT
# define DN_KEY_DOWN			GLFW_KEY_DOWN
# define DN_KEY_UP				GLFW_KEY_UP
# define DN_KEY_PAGE_UP			GLFW_KEY_PAGE_UP
# define DN_KEY_PAGE_DOWN		GLFW_KEY_PAGE_DOWN
# define DN_KEY_HOME			GLFW_KEY_HOME
# define DN_KEY_END				GLFW_KEY_END
# define DN_KEY_CAPS_LOCK		GLFW_KEY_CAPS_LOCK
# define DN_KEY_SCROLL_LOCK		GLFW_KEY_SCROLL_LOCK
# define DN_KEY_NUM_LOCK		GLFW_KEY_NUM_LOCK
# define DN_KEY_PRINT_SCREEN	GLFW_KEY_PRINT_SCREEN
# define DN_KEY_PAUSE			GLFW_KEY_PAUSE
# define DN_KEY_F1				GLFW_KEY_F1
# define DN_KEY_F2				GLFW_KEY_F2
# define DN_KEY_F3				GLFW_KEY_F3
# define DN_KEY_F4				GLFW_KEY_F4
# define DN_KEY_F5				GLFW_KEY_F5
# define DN_KEY_F6				GLFW_KEY_F6
# define DN_KEY_F7				GLFW_KEY_F7
# define DN_KEY_F8				GLFW_KEY_F8
# define DN_KEY_F9				GLFW_KEY_F9
# define DN_KEY_F10				GLFW_KEY_F10
# define DN_KEY_F11				GLFW_KEY_F11
# define DN_KEY_F12				GLFW_KEY_F12
# define DN_KEY_F13				GLFW_KEY_F13
# define DN_KEY_F14				GLFW_KEY_F14
# define DN_KEY_F15				GLFW_KEY_F15
# define DN_KEY_F16				GLFW_KEY_F16
# define DN_KEY_F17				GLFW_KEY_F17
# define DN_KEY_F18				LFW_KEY_F18
# define DN_KEY_F19				GLFW_KEY_F19
# define DN_KEY_F20				GLFW_KEY_F20
# define DN_KEY_F21				GLFW_KEY_F21
# define DN_KEY_F22				GLFW_KEY_F22
# define DN_KEY_F23				GLFW_KEY_F23
# define DN_KEY_F24				GLFW_KEY_F24
# define DN_KEY_F25				GLFW_KEY_F25
# define DN_KEY_KP_0			GLFW_KEY_KP_0
# define DN_KEY_KP_1			GLFW_KEY_KP_1
# define DN_KEY_KP_2			GLFW_KEY_KP_2
# define DN_KEY_KP_3			GLFW_KEY_KP_3
# define DN_KEY_KP_4			GLFW_KEY_KP_4
# define DN_KEY_KP_5			GLFW_KEY_KP_5
# define DN_KEY_KP_6			GLFW_KEY_KP_6
# define DN_KEY_KP_7			GLFW_KEY_KP_7
# define DN_KEY_KP_8			GLFW_KEY_KP_8
# define DN_KEY_KP_9			GLFW_KEY_KP_9
# define DN_KEY_KP_DECIMAL		GLFW_KEY_KP_DECIMAL
# define DN_KEY_KP_DIVIDE		GLFW_KEY_KP_DIVIDE
# define DN_KEY_KP_MULTIPLY		GLFW_KEY_KP_MULTIPLY
# define DN_KEY_KP_SUBTRACT		GLFW_KEY_KP_SUBTRACT
# define DN_KEY_KP_ADD			GLFW_KEY_KP_ADD
# define DN_KEY_KP_ENTER		GLFW_KEY_KP_ENTER
# define DN_KEY_KP_EQUAL		GLFW_KEY_KP_EQUAL
# define DN_KEY_LEFT_SHIFT		GLFW_KEY_LEFT_SHIFT
# define DN_KEY_LEFT_CONTROL	GLFW_KEY_LEFT_CONTROL
# define DN_KEY_LEFT_ALT		GLFW_KEY_LEFT_ALT
# define DN_KEY_LEFT_SUPER		GLFW_KEY_LEFT_SUPER
# define DN_KEY_RIGHT_SHIFT		GLFW_KEY_RIGHT_SHIFT
# define DN_KEY_RIGHT_CONTROL	GLFW_KEY_RIGHT_CONTROL
# define DN_KEY_RIGHT_ALT		GLFW_KEY_RIGHT_ALT
# define DN_KEY_RIGHT_SUPER		GLFW_KEY_RIGHT_SUPER
# define DN_KEY_MENU			GLFW_KEY_MENU
# define DN_KEY_LAST			GLFW_KEY_LAST

# define DN_MOUSE_1				GLFW_MOUSE_BUTTON_1
# define DN_MOUSE_2				GLFW_MOUSE_BUTTON_2
# define DN_MOUSE_3				GLFW_MOUSE_BUTTON_3
# define DN_MOUSE_4				GLFW_MOUSE_BUTTON_4
# define DN_MOUSE_5				GLFW_MOUSE_BUTTON_5
# define DN_MOUSE_6				GLFW_MOUSE_BUTTON_6
# define DN_MOUSE_7				GLFW_MOUSE_BUTTON_7
# define DN_MOUSE_8				GLFW_MOUSE_BUTTON_8
# define DN_MOUSE_LAST			GLFW_MOUSE_BUTTON_LAST
# define DN_MOUSE_LEFT			GLFW_MOUSE_BUTTON_LEFT
# define DN_MOUSE_RIGHT			GLFW_MOUSE_BUTTON_RIGHT
# define DN_MOUSE_MIDDLE		GLFW_MOUSE_BUTTON_MIDDLE

# define DN_NONE				GLFW_DONT_CARE

# define DN_CLOSED				(1 << 0)
# define DN_POS_SPECIFIED		(1 << 1)
# define DN_ICONIFIED			(1 << 2)
# define DN_VISIBLE				(1 << 3)
# define DN_AUTOCLEAR			(1 << 4)
# define DN_MAXIMIZED			(1 << 5)
# define DN_FREEATCLOSE			(1 << 6)
# define DN_FREEWINDOWS			(1 << 7)
# define DN_FLAG_NUM			8

# define DN_CUSTOM_FLAG0		(1 << (DN_FLAG_NUM + 0))
# define DN_CUSTOM_FLAG1		(1 << (DN_FLAG_NUM + 1))
# define DN_CUSTOM_FLAG2		(1 << (DN_FLAG_NUM + 2))
# define DN_CUSTOM_FLAG4		(1 << (DN_FLAG_NUM + 3))
# define DN_CUSTOM_FLAG5		(1 << (DN_FLAG_NUM + 4))

# define DN_POINTS				GL_POINTS
# define DN_LINES				GL_LINES
# define DN_LINE_LOOP			GL_LINE_LOOP
# define DN_LINE_STRIP			GL_LINE_STRIP
# define DN_TRIANGLES			GL_TRIANGLES
# define DN_TRIANGLE_STRIP		GL_TRIANGLE_STRIP
# define DN_TRIANGLE_FAN		GL_TRIANGLE_FAN
# define DN_LINES_ADJ			GL_LINES_ADJACENCY
# define DN_LINE_STRIP_ADJ		GL_LINE_STRIP_ADJACENCY
# define DN_TRIANGLES_ADJ		GL_TRIANGLES_ADJACENCY
# define DN_TRIANGLE_STRIP_ADJ	GL_TRIANGLE_STRIP_ADJACENCY

enum {
	DN_OK,
	DN_STOPPED,
	DN_GLFW_FAIL,
	DN_GLEW_FAIL,
	DN_ALRDY_RUNNING,
	DN_WINDOW_FAIL,
};

#endif // CODES_H
