$(function () {
    setContainerWrapperOverflowHidden();

    var hash = window.location.hash;

    if (hash) {
        hash.replace('#', '');

        if (hash.indexOf('como-funciona')) {
            hash = 'como-funciona-bloco';
        }

        window.scrollPage(hash);
    }
});

function setContainerWrapperOverflowHidden() {
    $(".container-wrapper").css('max-width', '100%');
    $(".container-wrapper").css('overflow-x', 'hidden');
}

function getHeightMenu() {
    var headerHeight = null;

    if ($(window).innerWidth() <= 768) {
        headerHeight = 52;
    } else {
        headerHeight = 129;
    }

    return headerHeight;
}

function scrollInHome(hash) {
    if (hash) {
        var headerHeight = getHeightMenu();

        $('html,body').animate({ scrollTop: $(hash + '-bloco').offset().top - headerHeight }, 'slow');
    }
}

$('.como-funciona-link').click(function () {
    scrollInHome('#como-funciona');
});