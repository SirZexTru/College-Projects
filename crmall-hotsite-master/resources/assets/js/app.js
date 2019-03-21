window.sliderLoaded = false;

(function () {
    "use strict";

    Ladda.bind('.ladda-button:not([disabled])');
    Ladda.bind('.ladda-sleep:not([disabled])', { timeout: 4000 });

    $('#main-menu-navbar-collapse').on('show.bs.collapse', function (e) {
        // Avoiding event fired on #nav-user-links
        if (e.target !== this) return;

        $('body').addClass('menu-visible');
    }).on('hidden.bs.collapse', function (e) {
        // Avoiding event fired on #nav-user-links
        if (e.target !== this) return;

        $('body').removeClass('menu-visible');
    });

    $(".form-validate").each(function () {
        $(this).validate({
            onkeyup: false,
            errorPlacement: function(error, element) {
                element.closest('.form-group').append(error);
            },
        });
    });

    window.scrollPage = function (id) {
        if(window.sliderLoaded) {
            let headerHeight = $('#main-menu').outerHeight();

            if($('#btn-new-coupon').length){
                headerHeight = headerHeight + 150;
            }

            $('html,body').animate({ scrollTop: $("#" + id).offset().top - headerHeight }, 'slow');
        } else {
            window.animateAfter = id;
        }
    };

    $(".navbar-nav li a").click(function(event) {
        if($(this).attr('href') !== '#nav-user-links') {
            $(".navbar-collapse").collapse('hide');
        }
    });

    $("#loginUserForm, #newUser, #editUser, #updatePassword").submit(function() {
        if(!$(this).valid()) {
            Ladda.stopAll();
        }
    });

    $('.flexslider').flexslider({
        animation: "slide",
        animationSpeed: 400,
        slideshowSpeed: 3500,
        start: function() {
            window.sliderLoaded = true;
            if(window.animateAfter) {
                $('html,body').waitForImages().done(function() {
                    scrollPage(window.animateAfter);
                });
            }
        },
    });
})();