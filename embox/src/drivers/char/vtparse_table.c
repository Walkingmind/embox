/**
 * @file
 * @brief State machine matrix for VTParse - DEC compatible parser.
 * @details VTParse is an implementation of Paul Williams' DEC compatible state
 * machine parser. For further information please refer
 * to http://vt100.net/emu/dec_ansi_parser.
 *
 * @date 04.02.2009
 * @author Joshua Haberman <joshua@reverberate.org>
 *          - Initial implementation using code generation from Ruby script
 * @author Eldar Abusalimov
 *          - Rewriting by hand using GNU C language extensions
 */

#include <drivers/vtparse_table.h>

/* Perform both action and the state change. */
#define TRANSIT(action, state) \
		VTPARSE_TRANSITION(VT_ACTION_ ## action, VTPARSE_STATE_ ## state)

/* Perform action without doing the state change. */
#define ACTION(action) \
		/* Well, in fact, there is no state change. Parser does not perform   \
		 * transition if state change field is 0 (= VTPARSE_STATE_ANYWHERE).*/\
		TRANSIT(action, ANYWHERE)

/* Every state includes some common transitions. */
#define ANYWHERE_TRANSITIONS \
				[0x18         ] = TRANSIT(EXECUTE, GROUND),         \
				[0x1a         ] = TRANSIT(EXECUTE, GROUND),         \
				[0x80 ... 0x8f] = TRANSIT(EXECUTE, GROUND),         \
				[0x91 ... 0x97] = TRANSIT(EXECUTE, GROUND),         \
				[0x99         ] = TRANSIT(EXECUTE, GROUND),         \
				[0x9a         ] = TRANSIT(EXECUTE, GROUND),         \
				[0x9c         ] = TRANSIT(NONE, GROUND), /* TODO check it. */ \
				[0x1b         ] = TRANSIT(NONE, ESCAPE),            \
				[0x98         ] = TRANSIT(NONE, SOS_PM_APC_STRING), \
				[0x9e         ] = TRANSIT(NONE, SOS_PM_APC_STRING), \
				[0x9f         ] = TRANSIT(NONE, SOS_PM_APC_STRING), \
				[0x90         ] = TRANSIT(NONE, DCS_ENTRY),         \
				[0x9d         ] = TRANSIT(NONE, OSC_STRING),        \
				[0x9b         ] = TRANSIT(NONE, CSI_ENTRY),

/* Uses GNU C designated initializers extension. */
__extension__
const vtparse_state_change_t vtparse_state_table[15][0x100] = {
		[VTPARSE_STATE_CSI_ENTRY] = {
				[0x00 ... 0x17] = ACTION(EXECUTE),
				[0x19         ] = ACTION(EXECUTE),
				[0x1c ... 0x1f] = ACTION(EXECUTE),
				[0x7f         ] = ACTION(IGNORE),
				[0x20 ... 0x2f] = TRANSIT(COLLECT, CSI_INTERMEDIATE),
				[0x3a         ] = TRANSIT(NONE, CSI_IGNORE),
				[0x30 ... 0x39] = TRANSIT(PARAM, CSI_PARAM),
				[0x3b         ] = TRANSIT(PARAM, CSI_PARAM),
				[0x3c ... 0x3f] = TRANSIT(COLLECT, CSI_PARAM),
				[0x40 ... 0x7e] = TRANSIT(CSI_DISPATCH,GROUND),
				ANYWHERE_TRANSITIONS
		},
		[VTPARSE_STATE_CSI_IGNORE] = {
				[0x00 ... 0x17] = ACTION(EXECUTE),
				[0x19         ] = ACTION(EXECUTE),
				[0x1c ... 0x1f] = ACTION(EXECUTE),
				[0x20 ... 0x3f] = ACTION(IGNORE),
				[0x7f         ] = ACTION(IGNORE),
				[0x40 ... 0x7e] = TRANSIT(NONE, GROUND),
				ANYWHERE_TRANSITIONS
		},
		[VTPARSE_STATE_CSI_INTERMEDIATE] = {
				[0x00 ... 0x17] = ACTION(EXECUTE),
				[0x19         ] = ACTION(EXECUTE),
				[0x1c ... 0x1f] = ACTION(EXECUTE),
				[0x20 ... 0x2f] = ACTION(COLLECT),
				[0x7f         ] = ACTION(IGNORE),
				[0x30 ... 0x3f] = TRANSIT(NONE, CSI_IGNORE),
				[0x40 ... 0x7e] = TRANSIT(CSI_DISPATCH, GROUND),
				ANYWHERE_TRANSITIONS
		},
		[VTPARSE_STATE_CSI_PARAM] = {
				[0x00 ... 0x17] = ACTION(EXECUTE),
				[0x19         ] = ACTION(EXECUTE),
				[0x1c ... 0x1f] = ACTION(EXECUTE),
				[0x30 ... 0x39] = ACTION(PARAM),
				[0x3b         ] = ACTION(PARAM),
				[0x7f         ] = ACTION(IGNORE),
				[0x3a         ] = TRANSIT(NONE, CSI_IGNORE),
				[0x3c ... 0x3f] = TRANSIT(NONE, CSI_IGNORE),
				[0x20 ... 0x2f] = TRANSIT(COLLECT, CSI_INTERMEDIATE),
				[0x40 ... 0x7e] = TRANSIT(CSI_DISPATCH, GROUND),
				ANYWHERE_TRANSITIONS
		},
		[VTPARSE_STATE_DCS_ENTRY] = {
				[0x00 ... 0x17] = ACTION(IGNORE),
				[0x19         ] = ACTION(IGNORE),
				[0x1c ... 0x1f] = ACTION(IGNORE),
				[0x7f         ] = ACTION(IGNORE),
				[0x3a         ] = TRANSIT(NONE, DCS_IGNORE),
				[0x20 ... 0x2f] = TRANSIT(COLLECT, DCS_INTERMEDIATE),
				[0x30 ... 0x39] = TRANSIT(PARAM, DCS_PARAM),
				[0x3b         ] = TRANSIT(PARAM, DCS_PARAM),
				[0x3c ... 0x3f] = TRANSIT(COLLECT, DCS_PARAM),
				[0x40 ... 0x7e] = TRANSIT(NONE, DCS_PASSTHROUGH),
				ANYWHERE_TRANSITIONS
		},
		[VTPARSE_STATE_DCS_IGNORE] = {
				[0x00 ... 0x17] = ACTION(IGNORE),
				[0x19         ] = ACTION(IGNORE),
				[0x1c ... 0x1f] = ACTION(IGNORE),
				[0x20 ... 0x7f] = ACTION(IGNORE),
				ANYWHERE_TRANSITIONS
		},
		[VTPARSE_STATE_DCS_INTERMEDIATE] = {
				[0x00 ... 0x17] = ACTION(IGNORE),
				[0x19         ] = ACTION(IGNORE),
				[0x1c ... 0x1f] = ACTION(IGNORE),
				[0x20 ... 0x2f] = ACTION(COLLECT),
				[0x7f         ] = ACTION(IGNORE),
				[0x30 ... 0x3f] = TRANSIT(NONE, DCS_IGNORE),
				[0x40 ... 0x7e] = TRANSIT(NONE, DCS_PASSTHROUGH),
				ANYWHERE_TRANSITIONS
		},
		[VTPARSE_STATE_DCS_PARAM] = {
				[0x00 ... 0x17] = ACTION(IGNORE),
				[0x19         ] = ACTION(IGNORE),
				[0x1c ... 0x1f] = ACTION(IGNORE),
				[0x30 ... 0x39] = ACTION(PARAM),
				[0x3b         ] = ACTION(PARAM),
				[0x7f         ] = ACTION(IGNORE),
				[0x3a         ] = TRANSIT(NONE, DCS_IGNORE),
				[0x3c ... 0x3f] = TRANSIT(NONE, DCS_IGNORE),
				[0x20 ... 0x2f] = TRANSIT(COLLECT, DCS_INTERMEDIATE),
				[0x40 ... 0x7e] = TRANSIT(NONE, DCS_PASSTHROUGH),
				ANYWHERE_TRANSITIONS
		},
		[VTPARSE_STATE_DCS_PASSTHROUGH] = {
				[0x00 ... 0x17] = ACTION(PUT),
				[0x19         ] = ACTION(PUT),
				[0x1c ... 0x1f] = ACTION(PUT),
				[0x20 ... 0x7e] = ACTION(PUT),
				[0x7f         ] = ACTION(IGNORE),
				ANYWHERE_TRANSITIONS
		},
		[VTPARSE_STATE_ESCAPE] = {
				[0x00 ... 0x17] = ACTION(EXECUTE),
				[0x19         ] = ACTION(EXECUTE),
				[0x1c ... 0x1f] = ACTION(EXECUTE),
#if 0
				[0x7f         ] = ACTION(IGNORE),
#else
				[0x7f         ] = ACTION(EXECUTE),
#endif
				[0x20 ... 0x2f] = TRANSIT(COLLECT, ESCAPE_INTERMEDIATE),
				[0x30 ... 0x4f] = TRANSIT(ESC_DISPATCH, GROUND),
				[0x51 ... 0x57] = TRANSIT(ESC_DISPATCH, GROUND),
				[0x59         ] = TRANSIT(ESC_DISPATCH, GROUND),
				[0x5a         ] = TRANSIT(ESC_DISPATCH, GROUND),
				[0x5c         ] = TRANSIT(ESC_DISPATCH, GROUND),
				[0x60 ... 0x7e] = TRANSIT(ESC_DISPATCH, GROUND),
				[0x5b         ] = TRANSIT(NONE, CSI_ENTRY),
				[0x5d         ] = TRANSIT(NONE, OSC_STRING),
				[0x50         ] = TRANSIT(NONE, DCS_ENTRY),
				[0x58         ] = TRANSIT(NONE, SOS_PM_APC_STRING),
				[0x5e         ] = TRANSIT(NONE, SOS_PM_APC_STRING),
				[0x5f         ] = TRANSIT(NONE, SOS_PM_APC_STRING),
				ANYWHERE_TRANSITIONS
		},
		[VTPARSE_STATE_ESCAPE_INTERMEDIATE] = {
				[0x00 ... 0x17] = ACTION(EXECUTE),
				[0x19         ] = ACTION(EXECUTE),
				[0x1c ... 0x1f] = ACTION(EXECUTE),
				[0x20 ... 0x2f] = ACTION(COLLECT),
				[0x7f         ] = ACTION(IGNORE),
				[0x30 ... 0x7e] = TRANSIT(ESC_DISPATCH, GROUND),
				ANYWHERE_TRANSITIONS
		},
		[VTPARSE_STATE_GROUND] = {
				[0x00 ... 0x17] = ACTION(EXECUTE),
				[0x19         ] = ACTION(EXECUTE),
				[0x1c ... 0x1f] = ACTION(EXECUTE),
				[0x20 ... 0x7e] = ACTION(PRINT),
#if 0
				[0x7f         ] = ACTION(PRINT),
#else
				[0x7f         ] = ACTION(EXECUTE),
#endif
				ANYWHERE_TRANSITIONS
		},
		[VTPARSE_STATE_OSC_STRING] = {
				[0x00 ... 0x17] = ACTION(IGNORE),
				[0x19         ] = ACTION(IGNORE),
				[0x1c ... 0x1f] = ACTION(IGNORE),
				[0x20 ... 0x7f] = TRANSIT(OSC_PUT, ANYWHERE),
				ANYWHERE_TRANSITIONS
		},
		[VTPARSE_STATE_SOS_PM_APC_STRING] = {
				[0x00 ... 0x17] = ACTION(IGNORE),
				[0x19         ] = ACTION(IGNORE),
				[0x1c ... 0x1f] = ACTION(IGNORE),
				[0x20 ... 0x7f] = ACTION(IGNORE),
				ANYWHERE_TRANSITIONS
		},
};

const VT_ACTION vtparse_state_entry_actions[] = {
		[VTPARSE_STATE_CSI_ENTRY]       = VT_ACTION_CLEAR,
		[VTPARSE_STATE_DCS_ENTRY]       = VT_ACTION_CLEAR,
		[VTPARSE_STATE_DCS_PASSTHROUGH] = VT_ACTION_HOOK,
		[VTPARSE_STATE_ESCAPE]          = VT_ACTION_CLEAR,
		[VTPARSE_STATE_OSC_STRING]      = VT_ACTION_OSC_START,
};

const VT_ACTION vtparse_state_exit_actions[] = {
		[VTPARSE_STATE_DCS_PASSTHROUGH] = VT_ACTION_UNHOOK,
		[VTPARSE_STATE_OSC_STRING]      = VT_ACTION_OSC_END,
};

