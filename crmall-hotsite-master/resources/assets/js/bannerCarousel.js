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

    $(self.images).hover(function() {
        self.stopAnimation();
    });

    $(self.images).mouseleave(function() {
        self.startAnimation();
    });
};

bannerCarousel.prototype.startInterval = function () {
    var self = this;

    self.interval = setInterval(function () {
        $(self.images[self.indexImg]).addClass('focused');

        if(self.indexImg === 0) {
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