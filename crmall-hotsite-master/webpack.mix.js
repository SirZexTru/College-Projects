let mix = require('laravel-mix');
let ImageminPlugin = require('imagemin-webpack-plugin').default;
let imageminMozjpeg = require('imagemin-mozjpeg');

require('dotenv').config();

mix.setPublicPath('public');

/*
 |--------------------------------------------------------------------------
 | Vendor assets bundle
 |--------------------------------------------------------------------------
 */
const mixStyles = [];

mixStyles.push('node_modules/ladda/dist/ladda-themeless.min.css');
mixStyles.push('node_modules/toastr/build/toastr.min.css');
mixStyles.push('node_modules/select2/dist/css/select2.min.css');

mixStyles.push('node_modules/flexslider/flexslider.css');
mix.copyDirectory('node_modules/flexslider/fonts/', 'public/css/fonts');

// Font-awesome
mixStyles.push('node_modules/font-awesome/css/font-awesome.min.css');
mix.copyDirectory('node_modules/font-awesome/fonts/', 'public/fonts');
mix.styles(mixStyles, 'public/css/vendor.css');

// Third party scripts
const vendorScripts = [];

vendorScripts.push('node_modules/jquery/dist/jquery.min.js');
vendorScripts.push('node_modules/bootstrap-sass/assets/javascripts/bootstrap.min.js');
vendorScripts.push('node_modules/jquery-validation/dist/jquery.validate.min.js');
vendorScripts.push('node_modules/jquery-validation/dist/localization/messages_pt_BR.js');
vendorScripts.push('node_modules/jquery-validation/dist/additional-methods.js');
vendorScripts.push('node_modules/jquery-mask-plugin/dist/jquery.mask.min.js');
vendorScripts.push('node_modules/jquery-maskmoney/dist/jquery.maskMoney.min.js');
vendorScripts.push('node_modules/waypoints/lib/jquery.waypoints.min.js');
vendorScripts.push('node_modules/ladda/dist/spin.min.js');
vendorScripts.push('node_modules/ladda/dist/ladda.min.js');
vendorScripts.push('node_modules/bootbox/bootbox.min.js');
vendorScripts.push('node_modules/toastr/build/toastr.min.js');
vendorScripts.push('node_modules/moment/min/moment.min.js');
vendorScripts.push('node_modules/moment/locale/pt-br.js');
vendorScripts.push('node_modules/select2/dist/js/select2.full.js');
vendorScripts.push('node_modules/flexslider/jquery.flexslider.js');
vendorScripts.push('node_modules/jquery.waitforimages/dist/jquery.waitforimages.js');

mix.babel(vendorScripts, 'public/js/vendor.js');

/*
 |--------------------------------------------------------------------------
 | App assets bundle
 |--------------------------------------------------------------------------
 */

/*
 * CSS
 */
mix.sass('resources/assets/sass/layout.scss', 'public/css/layout.css').options({processCssUrls: false});
mix.sass('resources/assets/sass/app.scss', 'public/css/app.css').options({processCssUrls: false});
mix.sass('resources/assets/sass/forgotPassword.scss', 'public/css/forgotPassword.css').options({processCssUrls: false});
mix.sass('resources/assets/sass/products_coupon.scss', 'public/css/products_coupons.css').options({processCssUrls: false});

// Fonts
mix.copyDirectory('resources/assets/fonts/', 'public/fonts');

// Specific page styles
const pageStyles = [];

pageStyles.forEach(function(pageStyle) {
    mix.copy(pageStyle, 'public/css/' + pageStyle.replace(/.*\//, ''));
});

/*
 * Javascripts
 */
// Specific page scripts
const pageScripts = [];
pageScripts.push('resources/assets/js/coupon.js');
pageScripts.push('resources/assets/js/user.js');
pageScripts.push('resources/assets/js/doubts.js');
pageScripts.push('resources/assets/js/home.js');
pageScripts.push('resources/assets/js/products_coupons.js');

pageScripts.forEach(function(pageScript) {
    mix.babel(pageScript, 'public/js/' + pageScript.replace(/.*\//, ''));
});

// General scripts / combined and compiled as app.js
const appScripts = [];
appScripts.push('resources/assets/js/_custom-validator-rules.js');
appScripts.push('resources/assets/js/imageLoader.js');
appScripts.push('resources/assets/js/bannerCarousel.js');
appScripts.push('resources/assets/js/app.js');

mix.babel(appScripts, 'public/js/app.js');

if (mix.inProduction()) {
    mix.webpackConfig({
        plugins: [
            new ImageminPlugin({
                test: /\.(jpe?g|png|gif|svg)$/i,
                plugins: [
                    imageminMozjpeg({
                        quality: 80,
                    })
                ]
            })
        ]
    });

    mix.version();
} else {
    mix.browserSync({
        proxy: process.env.APP_URL
    });
}

mix.babel(["resources/assets/js/admin.js"], "public/js/admin.js");
mix.sass("resources/assets/sass/layout-admin.scss", "public/css/layout-admin.css").options({processCssUrls: false});
