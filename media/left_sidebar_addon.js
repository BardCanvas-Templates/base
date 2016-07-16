
function toggle_left_sidebar_items()
{
    var visible        = $('#left_sidebar').is(':visible');
    var bar_visibility = visible ? 'false' : 'true';
    
    $('body').attr('data-left-sidebar-visible', bar_visibility);
}

$(document).ready(function()
{
    if( $(window).width() < 480 )
        $('body').attr('data-left-sidebar-visible', 'false');
    
    $(window).resize(function()
    {
        if( $('body').attr('data-left-sidebar-visible') == 'true' )
            toggle_left_sidebar_items();
    });
});
