$(function() {
    scrollPage('doubts-container');
});

$(".doubt .btn-circle").click(function() {
    if($(this).hasClass('active')) {
        $(this).html('+');
        $(this).removeClass('active');
        $(this).parent().parent().find('.doubt-title').removeClass('highlighted');
    } else {
        $(this).html('-');
        $(this).addClass('active');
        $(this).parent().parent().find('.doubt-title').addClass('highlighted');
    }
});

$('.doubt-title').click(function(){
    if($(this).hasClass('highlighted')) {
        $(this).removeClass('highlighted');
    } else{
        $(this).addClass('highlighted');
    }
});