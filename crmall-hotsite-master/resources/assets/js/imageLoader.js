function imageLoader(images, loadedCallback) {
    this.loadedCallback = loadedCallback;
    this.loadImages(images);
}

imageLoader.prototype.constructor = imageLoader;

imageLoader.prototype.onComplete = function(length, index) {

    if(parseInt(length) === parseInt(index)) {
        this.loadedCallback();
    }
};

imageLoader.prototype.loadImages = function(images) {
    var self = this;
    $(images).each(function() {
        var imgSrc = $(this).attr('src');
        $(this).on('load' , function() {
            self.onComplete(images.length, $(this).data('id'));
        });
        $(this).attr('src', imgSrc);
    });
};
