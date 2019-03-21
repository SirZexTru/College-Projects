$.validator.addMethod('blockFutureDate', function (value) {
    return !(moment(value, 'DD/MM/YYYY', true) > moment());
}, 'A data é maior que a data de hoje');

$.validator.addMethod('age', function (value) {
    value = value.split('/');
    value = value[2] + '-' + value[1] + '-' + value[0];

    var birthDate = new Date(value);
    var age = ~~((Date.now() - birthDate) / 31557600000);

    return age >= 18;
}, 'Precisa-se ter mais de 18 anos para participar');

$.extend($.validator.messages, {
    required: "Este campo &eacute; obrigat&oacute;rio.",
    cpfBR: "Digite um CPF válido"
});

$.validator.addMethod('validPhone', function (value) {
    return value.length >= 13;
}, 'Telefone inválido');
function imageLoader(images, loadedCallback) {
    this.loadedCallback = loadedCallback;
    this.loadImages(images);
}

imageLoader.prototype.constructor = imageLoader;

imageLoader.prototype.onComplete = function (length, index) {

    if (parseInt(length) === parseInt(index)) {
        this.loadedCallback();
    }
};

imageLoader.prototype.loadImages = function (images) {
    var self = this;
    $(images).each(function () {
        var imgSrc = $(this).attr('src');
        $(this).on('load', function () {
            self.onComplete(images.length, $(this).data('id'));
        });
        $(this).attr('src', imgSrc);
    });
};

function bannerCarousel(images, time) {
    this.indexImg = 0;
    this.images = images;
    this.time = time;
    this.interval = null;

    this.startAnimation();
    this.detectHover();
}

bannerCarousel.prototype.constructor = bannerCarousel;

bannerCarousel.prototype.detectHover = function () {
    var self = this;

    $(self.images).hover(function () {
        self.stopAnimation();
    });

    $(self.images).mouseleave(function () {
        self.startAnimation();
    });
};

bannerCarousel.prototype.startInterval = function () {
    var self = this;

    self.interval = setInterval(function () {
        $(self.images[self.indexImg]).addClass('focused');

        if (self.indexImg === 0) {
            $(self.images[self.images.length - 1]).removeClass('focused');
        } else {
            $(self.images[self.indexImg - 1]).removeClass('focused');
        }

        self.indexImg === self.images.length - 1 ? self.indexImg = 0 : self.indexImg++;
    }, self.time);
};

bannerCarousel.prototype.stopAnimation = function () {
    var self = this;
    clearInterval(self.interval);
    $(self.images).each(function () {
        $(this).removeClass('focused');
    });
};

bannerCarousel.prototype.startAnimation = function () {
    var self = this;
    self.indexImg = 0;
    self.startInterval();
};
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
            errorPlacement: function errorPlacement(error, element) {
                element.closest('.form-group').append(error);
            }
        });
    });

    window.scrollPage = function (id) {
        if (window.sliderLoaded) {
            var headerHeight = $('#main-menu').outerHeight();

            if ($('#btn-new-coupon').length) {
                headerHeight = headerHeight + 150;
            }

            $('html,body').animate({ scrollTop: $("#" + id).offset().top - headerHeight }, 'slow');
        } else {
            window.animateAfter = id;
        }
    };

    $(".navbar-nav li a").click(function (event) {
        if ($(this).attr('href') !== '#nav-user-links') {
            $(".navbar-collapse").collapse('hide');
        }
    });

    $("#loginUserForm, #newUser, #editUser, #updatePassword").submit(function () {
        if (!$(this).valid()) {
            Ladda.stopAll();
        }
    });

    $('.flexslider').flexslider({
        animation: "slide",
        animationSpeed: 400,
        slideshowSpeed: 3500,
        start: function start() {
            window.sliderLoaded = true;
            if (window.animateAfter) {
                $('html,body').waitForImages().done(function () {
                    scrollPage(window.animateAfter);
                });
            }
        }
    });
})();