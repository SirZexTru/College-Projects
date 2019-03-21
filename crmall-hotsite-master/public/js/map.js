(function ($) {
    var mapaRiogaleao = {
        map: false,
        element: false,
        wrapper: false,
        themePath: false,
        items: false,
        styles: false,
        ps: false,
        btnMapLeft: false,
        btnMapRight: false,
        infoWindowActiveClass: 'marker-show',
        init: function (context, settings) {
            var self = this;
            self.wrapper = document.querySelector('#block--mapa--riogaleao');
            self.element = self.wrapper.querySelector('.map');

            if (self.element) {
                if (window.scriptMapa === undefined) {
                    var key = "AIzaSyDHlKCMGq0frMiJDz5TA1mFsHdYdiFJ_9U";
                    self.items = self.items || [];
                    if (key) {
                        var script = document.createElement('script');
                        script.type = 'text/javascript';
                        script.src = 'https://maps.googleapis.com/maps/api/js?v=3.exp&key=' + key + '&callback=mapaRiogaleao.initMapa';
                        document.body.appendChild(script);

                        self.initMapa = self.initMapa.bind(this);
                        self.createControlMapButtons = self.createControlMapButtons.bind(this);
                        self.insertItems = self.insertItems.bind(this);
                        self.createMarker = self.createMarker.bind(this);
                        self.getMarkerByNid = self.getMarkerByNid.bind(this);
                        self.closeInfoWindow = self.closeInfoWindow.bind(this);
                        self.openInfoWindow = self.openInfoWindow.bind(this);
                        self.createInfoWindow = self.createInfoWindow.bind(this);
                    }
                }
            }
        },
        initMapa: function  () {
            var self = this;
            if (!self.map) {
                var lat = -13.579376258290615;
                var lon = -52.873377799987736;
                var myLatlng = new google.maps.LatLng(lat, lon);

                var mapOptions = {
                    center: myLatlng,
                    disableDoubleClickZoom: true,
                    zoomControlOptions: false,
                    zoom: 2,
                    disableDefaultUI: true,
                    zoomControl: false,
                    mapTypeControl: false,
                    streetViewControl: false,
                    scaleControl: false,
                    rotateControl: false,
                    fullscreenControl: false
                };
                if (self.styles) {
                    mapOptions.styles = self.styles;
                }
                self.map = new google.maps.Map(self.element, mapOptions);
                google.maps.event.addListener(self.map, 'tilesloaded', self.createControlMapButtons);
            }

            if (self.items && self.items.length > 0 ) {
                self.insertItems();
            }
        },
        createControlMapButtons: function () {
            var self = this;
            if (!self.btnMapLeft) {
                self.btnMapLeft = document.createElement('button');
                self.btnMapLeft.setAttribute('class', 'btn--movemap btn--movemap--left');
                self.btnMapLeft.setAttribute('onclick', 'mapaRiogaleao.mapMoveLeft()');
                self.btnMapLeft.appendChild(document.createTextNode('Mover para esquerda'));
                self.wrapper.appendChild(self.btnMapLeft);
            }

            if (!self.btnMapRight) {
                self.btnMapRight = document.createElement('button');
                self.btnMapRight.setAttribute('class', 'btn--movemap btn--movemap--right');
                self.btnMapRight.setAttribute('onclick', 'mapaRiogaleao.mapMoveRight()');
                self.btnMapRight.appendChild(document.createTextNode('Mover para direita'));
                self.wrapper.appendChild(self.btnMapRight);
            }
            google.maps.event.clearListeners(self.map, 'tilesloaded');
        },
        mapPixelMove : 20,
        mapMove: function(center, x, y) {
            var self = this;
            var projection = self.map.getProjection();
            var point = projection.fromLatLngToPoint(center);
            if (x) {
                point.x = point.x + x;
            }

            if (y) {
                point.y = point.y + y;
            }

            newCenter = projection.fromPointToLatLng(point);
            self.map.panTo(newCenter);
        },
        mapMoveLeft: function() {
            var self = this;
            var center = self.map.getCenter();
            self.mapMove(center, -1*self.mapPixelMove);
        },
        mapMoveRight: function() {
            var self = this;
            var center = self.map.getCenter();
            self.mapMove(center, self.mapPixelMove);
        },
        bounds: false,
        timeStep: 100,
        insertItems: function () {
            var self = this;
            self.bounds = new google.maps.LatLngBounds();

            for (item in self.items ) {
                if (!self.items[item].marker) {
                    self.items[item].key = item;
                    self.createMarker(self.items[item]);
                }
            }

            window.setTimeout(function () {
                // zoom = self.map.getZoom();
                self.map.fitBounds(self.bounds);
                // self.map.setZoom(zoom);
            }, self.items.length * self.timeStep);
        },
        createMarker: function (item) {
            var self = this;
            var labelBox = self.createLabelBox(item);
            var infoWindow = self.createInfoWindow(item);
            var position = new google.maps.LatLng(item.latitude, item.longitude);
            var markerOptions = {
                map: self.map,
                position: position,
                draggable: false,
                nid: item.nid,
                open: false,
                labelBox: labelBox,
                infoWindow: infoWindow,
                title: item.codigo ? item.codigo : item.title,
                animation: google.maps.Animation.DROP
            };

            var icon = false;
            self.bounds.extend(position);
            if (self.themePath) {
                switch (item.tipo) {
                    case 'nacional':
                        icon = self.themePath + 'images/marker-nacional.png';
                        break;
                    case 'internacional':
                        icon = self.themePath + 'images/marker-internacional.png';
                        break;
                    case 'riogaleao':
                        icon = self.themePath + 'images/marker-riogaleao.png';
                        break;
                    default:
                        icon = self.themePath + 'images/marker-nacional.png';
                        break;
                }
            }
            if (icon) {
                markerOptions.icon = icon;
            }
            window.setTimeout(function () {
                marker = new google.maps.Marker(markerOptions);
                marker.ps = new PerfectScrollbar('#marker-info-' + item.nid + ' .marker-info--body');

                google.maps.event.addListener(marker, 'click', function (event) {
                    self.openInfoWindow(this.nid);

                });

                google.maps.event.addListener(marker, 'mouseout', function (event) {
                    self.closeLabelBox(this.nid);
                });


                google.maps.event.addListener(marker, 'mouseover', function (event) {
                    self.openLabelBox(this.nid);
                });
                item.marker = marker;
            }, item.key * self.timeStep);
        },
        createLabelBox: function (item) {
            var self = this;
            var position = new google.maps.LatLng(item.latitude, item.longitude);
            var infowindow = new google.maps.InfoWindow({
                content: item.codigo ? item.codigo : item.title,
                disableAutoPan: false,
            });
            google.maps.event.addListener(infowindow, 'domready', function (event) {
                var iwOuter = $('.gm-style-iw');
                var iwCloseBtn = iwOuter.next();
                iwCloseBtn.remove();
            });

            infowindow.close();
            return infowindow;
        },
        createInfoWindow: function (item) {
            var self = this;
            var infoWindow;
            var infoWindowTitle;
            var infoWindowBody;

            infoWindow = document.createElement('div');

            infoWindow.setAttribute('id', 'marker-info-' + item.nid);
            infoWindow.setAttribute('data-nid', item.nid);
            infoWindow.setAttribute('class', 'marker-info');

            infoWindowClose = document.createElement('button');
            infoWindowClose.setAttribute('class', 'marker-info--close');
            infoWindowClose.setAttribute('onclick', 'mapaRiogaleao.closeInfoWindow(' + item.nid + ')');
            infoWindowClose.appendChild(document.createTextNode('Fechar'));

            infoWindow.appendChild(infoWindowClose);

            infoWindowTitle = document.createElement('h4');
            infoWindowTitle.setAttribute('class', 'marker-info--title');
            infoWindowTitle.appendChild(document.createTextNode(item.title));
            infoWindow.appendChild(infoWindowTitle);

            if (item.thumb) {
                infoWindowThumbWrapper = document.createElement('div');
                infoWindowThumbWrapper.setAttribute('class', 'marker-info--thumb');

                infoWindowThumb = document.createElement('img');
                infoWindowThumb.setAttribute('src', item.thumb);
                infoWindowThumbWrapper.appendChild(infoWindowThumb);
                infoWindow.appendChild(infoWindowThumbWrapper);
            }

            // infoWindowThumbWrapper.innerHTML = item.ThumbWrapper;

            infoWindowBody = document.createElement('div');
            infoWindowBody.setAttribute('class', 'marker-info--body');
            infoWindowBody.innerHTML = item.body;

            infoWindow.appendChild(infoWindowBody);

            self.wrapper.appendChild(infoWindow);
            return infoWindow;
        },
        getMarkerByNid: function (nid) {
            var self = this;
            for (item in self.items) {
                if (self.items[item].nid == nid && self.items[item].marker) {
                    return self.items[item].marker;
                }
            }
        },
        findOpenInfoWindow: function () {
            var self = this;
            for (item in self.items) {
                if (self.items[item].marker && self.items[item].marker.open) {
                    return self.items[item].marker;
                }
            }
        },
        openLabelBox: function (nid) {
            var self = this;
            marker = self.getMarkerByNid(nid);
            if (marker && !marker.opened) {
                marker.labelBox.open(self.map, marker);
            }
        },
        closeLabelBox: function (nid) {
            var self = this;
            marker = self.getMarkerByNid(nid);
            if (marker) {
                marker.labelBox.close();
            }
        },
        openInfoWindow: function (nid) {
            var self = this;

            var marker = self.getMarkerByNid(nid);

            if (marker && !marker.open) {
                var opened = self.findOpenInfoWindow();
                if (opened) {
                    self.closeInfoWindow(opened.nid);
                }
                self.map.setOptions({ draggable: false });
                marker.open = true;
                marker.infoWindow.classList.add(self.infoWindowActiveClass);
                marker.setAnimation(google.maps.Animation.BOUNCE);
            }
        },
        closeInfoWindow: function (nid) {
            var self = this;

            marker = self.getMarkerByNid(nid);

            self.map.setOptions({ draggable: true });
            if (marker) {
                marker.open = false;
                marker.infoWindow.classList.remove(self.infoWindowActiveClass);
                marker.setAnimation(false);
            }
        },
        mapaStyles: [
            {
                "featureType": "administrative",
                "elementType": "all",
                "stylers": [
                    {
                        "visibility": "on"
                    },
                    {
                        "saturation": -100
                    },
                    {
                        "lightness": 20
                    }
                ]
            },
            {
                "featureType": "road",
                "elementType": "all",
                "stylers": [
                    {
                        "visibility": "on"
                    },
                    {
                        "saturation": -100
                    },
                    {
                        "lightness": 40
                    }
                ]
            },
            {
                "featureType": "water",
                "elementType": "all",
                "stylers": [
                    {
                        "visibility": "on"
                    },
                    {
                        "saturation": -10
                    },
                    {
                        "lightness": 30
                    }
                ]
            },
            {
                "featureType": "landscape.man_made",
                "elementType": "all",
                "stylers": [
                    {
                        "visibility": "simplified"
                    },
                    {
                        "saturation": -60
                    },
                    {
                        "lightness": 10
                    }
                ]
            },
            {
                "featureType": "landscape.natural",
                "elementType": "all",
                "stylers": [
                    {
                        "visibility": "simplified"
                    },
                    {
                        "saturation": -60
                    },
                    {
                        "lightness": 60
                    }
                ]
            },
            {
                "featureType": "poi",
                "elementType": "all",
                "stylers": [
                    {
                        "visibility": "off"
                    },
                    {
                        "saturation": -100
                    },
                    {
                        "lightness": 60
                    }
                ]
            },
            {
                "featureType": "transit",
                "elementType": "all",
                "stylers": [
                    {
                        "visibility": "off"
                    },
                    {
                        "saturation": -100
                    },
                    {
                        "lightness": 60
                    }
                ]
            }
        ],
    };
    window.mapaRiogaleao = mapaRiogaleao;

    $.getJSON('/js/map-points.js', function(data){
        console.log(data);
        mapaRiogaleao.themePath = data.themePath;
        mapaRiogaleao.styles = data.styles;
        mapaRiogaleao.items = data.items;
        mapaRiogaleao.init();
    })
})(jQuery);