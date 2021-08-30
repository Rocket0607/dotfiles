/*
  4coder_default_bidings.cpp - Supplies the default bindings used for default 4coder behavior.
*/

// TOP
/*
  4coder_default_bidings.cpp - Supplies the default bindings used for default 4coder hbehavior.
*/

// TOP
hello
// TODO: Change colors (make them better)
// TODO: Setup mode for window/panel manipulation (w in emacs. ex. SPC w c)
// TODO: Setup keybinding for going forwards and backwards by words (w and b respectively in vim)
// TODO: Setup replace mode
// TODO: Setup keybinding for inserting in quotes, brackets, etc.

!defined(FCODER_DEFAULT_BINDINGS_CPP)
#define FCODER_DEFAULT_BINDINGS_CPP

#include "4coder_default_include.cpp"

// NOTE(allen): Users can declare their own managed IDs here.

#include "generated/managed_id_metadata.cpp"

String_ID mapid_shared;
String_ID mapid_command;
String_ID mapid_normal;
String_ID mapid_insert;
String_ID mapid_command_key;
String_ID mapid_delete;
String_ID mapid_change;

void set_current_mapid( Application_Links* app, Command_Map_ID mapid ) {
    
    View_ID view = get_active_view( app, 0 );
    Buffer_ID buffer = view_get_buffer( app, view, 0 );
    Managed_Scope scope = buffer_get_managed_scope( app, buffer );
    Command_Map_ID* map_id_ptr = scope_attachment( app, scope, buffer_map_id, Command_Map_ID );
    *map_id_ptr = mapid;
}

CUSTOM_COMMAND_SIG( go_to_command_mode ) {
    set_current_mapid( app, mapid_command );
    
    active_color_table.arrays[defcolor_margin_active].vals[0] = 0xff323232;
}

CUSTOM_COMMAND_SIG(modal_save){
    save(app);
}

CUSTOM_COMMAND_SIG( go_to_normal_mode ) {
    
    set_current_mapid( app, mapid_normal );
    
    active_color_table.arrays[ defcolor_cursor ].vals[ 0 ] = 0xffff5533;
    active_color_table.arrays[ defcolor_at_cursor ].vals[ 0 ] = 0xff00aacc;
    active_color_table.arrays[ defcolor_margin_active ].vals[ 0 ] = 0xffff5533;
}

CUSTOM_COMMAND_SIG( move_right_by_word ) {
    move_right_alpha_numeric_boundary(app);
    move_right(app);
}

CUSTOM_COMMAND_SIG( move_left_by_word ) {
    move_left_alpha_numeric_boundary(app);
    move_left(app);
}

CUSTOM_COMMAND_SIG( go_to_insert_mode ) {
    
    set_current_mapid( app, mapid_insert );
    
    active_color_table.arrays[ defcolor_cursor ].vals[ 0 ] = 0xff80ff80;
    active_color_table.arrays[ defcolor_at_cursor ].vals[ 0 ] = 0xff293134;
    active_color_table.arrays[ defcolor_margin_active ].vals[ 0 ] = 0xff80ff80;
}

CUSTOM_COMMAND_SIG( command_key ) {
    
    set_current_mapid( app, mapid_command_key );
    
    active_color_table.arrays[ defcolor_margin_active ].vals[ 0 ] = 0xff5555ff;
}

CUSTOM_COMMAND_SIG( go_to_delete_mode ) {
    
    set_current_mapid( app, mapid_delete );
    
    active_color_table.arrays[ defcolor_cursor ].vals[ 0 ] = 0xffffff00;
    active_color_table.arrays[ defcolor_at_cursor ].vals[ 0 ] = 0xff0000ff;
}

CUSTOM_COMMAND_SIG( modal_delete_word_left ) {
    backspace_alpha_numeric_boundary( app );
    go_to_normal_mode( app );
}

CUSTOM_COMMAND_SIG( modal_delete_word_right ) {
    delete_alpha_numeric_boundary( app );
    go_to_normal_mode( app );
}

CUSTOM_COMMAND_SIG( modal_delete_line ) {
    delete_line( app );
    go_to_normal_mode( app );
}

CUSTOM_COMMAND_SIG( go_to_change_mode ) {
    
    set_current_mapid( app, mapid_change );
    
    active_color_table.arrays[ defcolor_cursor ].vals[ 0 ] = 0xffffff00;
    active_color_table.arrays[ defcolor_at_cursor ].vals[ 0 ] = 0xff0000ff;
}

CUSTOM_COMMAND_SIG( modal_change_word_right ) {
    delete_alpha_numeric_boundary( app );
    go_to_insert_mode( app );
}

CUSTOM_COMMAND_SIG( modal_change_word_left ) {
    backspace_alpha_numeric_boundary( app );
    go_to_insert_mode( app );
}

CUSTOM_COMMAND_SIG( newline_and_insert ) {
    seek_end_of_line(app);
    String_Const_u8 newline;
    u8 newline_char = '\n';
    newline.str = &newline_char;
    newline.size = sizeof(char);
    write_string(app, newline);
    go_to_insert_mode(app);
}

void
custom_layer_init(Application_Links *app){
    Thread_Context *tctx = get_thread_context(app);
    
    // NOTE(allen): setup for default framework
    default_framework_init(app);
    
    // NOTE(allen): default hooks and command maps
    set_all_default_hooks(app);
    mapping_init(tctx, &framework_mapping);
    
    String_ID global_map_id = vars_save_string_lit("keys_global");
    String_ID file_map_id = vars_save_string_lit("keys_file");
    String_ID code_map_id = vars_save_string_lit("keys_code");
    
    mapid_shared = vars_save_string_lit( "mapid_shared" );
    mapid_normal = vars_save_string_lit( "mapid_normal" );
    mapid_insert = vars_save_string_lit( "mapid_insert" );
    mapid_command_key = vars_save_string_lit( "mapid_command_key" );
    mapid_delete = vars_save_string_lit( "mapid_delete" );
    mapid_change = vars_save_string_lit( "mapid_change" );
    
    MappingScope( );
    SelectMapping( &framework_mapping );
    
    SelectMap( global_map_id );
    
    //Keybinds that will work throughout all modes
    SelectMap( mapid_shared );
    BindCore( default_startup, CoreCode_Startup );
    BindCore( default_try_exit, CoreCode_TryExit );
    Bind( go_to_normal_mode, KeyCode_Escape );
    Bind( move_left, KeyCode_Left );
    Bind( move_right, KeyCode_Right );
    Bind( move_up, KeyCode_Up );
    Bind( move_down, KeyCode_Down );
    
    //NORMAL MODE
    SelectMap( mapid_normal );
    ParentMap( mapid_shared );
    // Switch Modes
    Bind( go_to_insert_mode, KeyCode_I );
    Bind( go_to_delete_mode, KeyCode_D );
    Bind( go_to_change_mode, KeyCode_C );
    Bind( command_key, KeyCode_Space );
    Bind(go_to_command_mode, KeyCode_Semicolon, KeyCode_Shift);
    // Movement )
    Bind( move_left, KeyCode_H );
    Bind( move_right, KeyCode_L );
    Bind( move_up, KeyCode_K );
    Bind( move_down, KeyCode_J );
    Bind( goto_beginning_of_file, KeyCode_G );
    Bind( goto_end_of_file, KeyCode_G, KeyCode_Shift );
    Bind( seek_end_of_line, KeyCode_4, KeyCode_Shift );
    Bind( seek_beginning_of_line, KeyCode_0 );
    Bind( search, KeyCode_ForwardSlash );
    Bind( newline_and_insert, KeyCode_O );
    // Deletion of chars in normal mode
    Bind(backspace_char, KeyCode_Backspace);
    Bind(delete_char, KeyCode_Delete);
    // Misc
    Bind(paste, KeyCode_P);
    Bind(undo, KeyCode_U);
    
    //COMMAND MODE
    Bind(save, KeyCode_W);
    Bind(go_to_normal_mode, KeyCode_Return);
    
    //INSERT MODE
    SelectMap( mapid_insert );
    ParentMap( mapid_shared );
    BindTextInput( write_text_and_auto_indent );
    Bind(backspace_char, KeyCode_Backspace);
    Bind(delete_char, KeyCode_Delete);
    Bind(modal_change_word_left, KeyCode_Backspace, KeyCode_Control);
    
    //Mode for keybinds for shortcuts (similar to keychords in emacs) (start siwth Space, then followed by key representing function to be called)
    SelectMap( mapid_command_key );
    Bind( go_to_normal_mode, KeyCode_Escape );
    Bind( change_active_panel, KeyCode_L );
    Bind( change_active_panel_backwards, KeyCode_H );
    Bind( interactive_open_or_new , KeyCode_Period );
    Bind( command_lister , KeyCode_Space );
    
    // DELETE MODE
    SelectMap( mapid_delete );
    Bind( go_to_normal_mode, KeyCode_Escape );
    Bind( modal_delete_word_left, KeyCode_H );
    Bind( modal_delete_word_right, KeyCode_L );
    Bind( modal_delete_word_right, KeyCode_W );
    Bind ( modal_delete_line, KeyCode_D );
    
    //CHANGE MODE
    SelectMap( mapid_change );
    Bind( go_to_normal_mode, KeyCode_Escape );
    Bind( modal_change_word_left, KeyCode_H );
    Bind( modal_change_word_right, KeyCode_L );
    Bind( modal_change_word_right, KeyCode_W );
    
    /* This is to make sure that the default bindings on the buffers will be mapid_normal. */
    SelectMap( file_map_id );
    ParentMap( mapid_normal );
    
    SelectMap( code_map_id );
    ParentMap( mapid_normal );
}

#endif //FCODER_DEFAULT_BINDINGS

// BOTTOM
