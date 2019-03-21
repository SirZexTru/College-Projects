let validator = null;
let allowSubmitForm = false;
let products = {};
let qtdTotal = 0;
let valueTotal = 0;
let valueTotalMaskMoney = 0;
let stores = [];
let resizedImage = {};

$(document).ready(onReady);

function onReady()
{
    maskElements();
    validation();
    scrollPage('new-coupon');
    getStores();
    initProductsList();
}

function initProductsList()
{
    if(hasProductsList) {
        $('#productSearch').select2({
            ajax: {
                url: '/search/products',
                dataType: 'json'
            },
            delay: 250,
            minimumInputLength: 4,
            placeholder: 'Digite o código ou nome do produto'
        }).on('select2:select', function (e) {
            setTimeout(function() {
                $("#quantityNumber").val(1).focus();
                $('#productValue').removeAttr('disabled');

                $("#quantityNumber").removeAttr('disabled');
                $(".plus, .minus").removeClass('disabled');
            }, 1);
        });

        $("#quantityNumber, #productValue").keyup(function(){
            if($('#quantityNumber').val() && $('#productValue').val() && $('#productSearch').val()) {
                $('#btnAddProduct').removeAttr('disabled');
            }else{
                $('#btnAddProduct').attr('disabled', true);
            }
        });

        $("#quantityNumber").on('input', function() {
            if(!$(this).val() || $(this).val() < 0) {
                $('#btnAddProduct').attr('disabled', true);
            } else {
                $('#btnAddProduct').removeAttr('disabled');
            }
        });

        $("#btnAddProduct").click(function() {
            let quantity = parseInt($("#quantityNumber").val());
            let value = parseFloat($("#productValue").val().replace(/\./gi, '').replace(/,/gi, '.')) * quantity;
            let product = $('#productSearch').val().split('_');
            let totalProducts = $('.productSelectionContainer.result #totalProducts');
            let totalValue = $('.productSelectionContainer.result #totalValue');
            let valueMaskMoney = 0;

            if (typeof product[0] === 'string' || product[0] instanceof String) {
                let numbers = product[0].match(/\d/g);
                numbers = numbers.join("");
                product[0] = numbers;
            }

            if (quantity > 0) {
                qtdTotal = totalProducts.text()?parseInt(totalProducts.text()):0;

                if ($('#product-' + product[0]).length) {
                    let actualQtd = $('#product-' + product[0] + ' .qtd-value');
                    let actualValue = $('#product-' + product[0] + ' .value');

                    let qtdCalculated = parseInt(actualQtd.text()) + quantity;
                    let qtdValue = parseFloat(products[product[0]].productValue) + value;

                    products[product[0]].qtd = qtdCalculated;
                    products[product[0]].productValue = qtdValue;
                    products[product[0]].productValueMaskMoney = qtdValue;

                    actualQtd.text(qtdCalculated);
                    actualValue.text(products[product[0]].productValueMaskMoney.toLocaleString('pt-br',{style: 'currency', currency: 'BRL'}));

                } else {

                    valueMaskMoney = value.toLocaleString('pt-br',{style: 'currency', currency: 'BRL'});

                    let div = '<div class="col-md-12" id="product-' + product[0] + '">\n' +
                        '                            <div class="product-list">\n' +
                        '                                <div class="name">\n' +
                        '                                    <p>' + product[1] + '</p>\n' +
                        '                                </div>\n' +
                        '                                <div>\n' +
                        '                                    <p><strong>Qtd:</strong> <span class="qtd-value">' + quantity + ' </span></p>\n' +
                        '                                </div>\n' +
                        '                                <div class="numbers">\n' +
                        '                                    <p><strong>Valor:</strong>  R$ <span class="value">' + valueMaskMoney + '</span></p>\n' +
                        '                                </div>\n' +
                        '                            </div>\n' +
                        '                        </div>';

                    products[product[0]] = {
                        qtd: quantity,
                        productName: product[1],
                        productBarCode: product[0],
                        productValue: value,
                        productValueMaskMoney: valueMaskMoney
                    };

                    $(div).prependTo('#products-list');
                }

                qtdTotal = qtdTotal + quantity;
                valueTotal = valueTotal + value;
                valueTotalMaskMoney = valueTotal.toLocaleString('pt-br',{style: 'currency', currency: 'BRL'});

                totalProducts.text( qtdTotal );
                totalValue.text( valueTotalMaskMoney );

                $('.productSelectionContainer.result').show();
                allowSubmitForm = true;
                resetProductSearch();
            }
        });

        $(".plus").click(function() {
            if(!$(this).hasClass('disabled')) {
                let $quantityElem = $(this).prev().find('input');
                let quantity = parseInt($quantityElem.val());

                $quantityElem.val(quantity + 1);
            }
        });

        $(".minus").click(function() {
            if(!$(this).hasClass('disabled')) {
                let $quantityElem = $(this).next().find('input');
                let quantity = parseInt($quantityElem.val());

                if(quantity > 0) {
                    $quantityElem.val(quantity - 1);
                }
            }
        });
    } else {
        allowSubmitForm = true;
    }
}

function maskElements()
{
    $('.cnpj-mask').mask('00.000.000/0000-00', {reverse: true});
    $('.date-mask').mask('00/00/0000');
    $('.money-mask').mask('#.##0,00', {reverse: true});
}

function validation()
{
    $.validator.addMethod('brDate', function(value) {
        return (value.length === 0) || moment(value, 'DD/MM/YYYY', true).isValid();
    }, 'Data inválida');

    $.validator.addMethod('blockFutureDate', function(value) {
        return !(moment(value, 'DD/MM/YYYY', true) > moment());
    }, 'A data é maior que a data de hoje');

    $.validator.messages.required = 'Campo obrigatório';

    validator = $('#invoice-form').validate({
        rules: {
            date: {
                brDate: true,
                blockFutureDate: true
            }
        },
        onkeyup :false,
        submitHandler: submitForm,
        invalidHandler: function(event, validator) {
            Ladda.stopAll();
        },
        errorPlacement: function(error, element)
        {
            if ( element.is(":radio") ) {
                error.appendTo( element.parent().parent());
                error.css('color', 'red');
                error.css('font-size', '12px');
            } else {
                error.insertAfter( element );
            }
        },
    });
}

$('input[name=question]').change(function(){
    let question = $('input[name=question]:checked').val() === 'riogaleao';

    if(!question) {
        $('#questionRequired').show();
        $('#send-button').attr('disabled', true).addClass('disabled');
    }else{
        $('#questionRequired').hide();
        $('#send-button').attr('disabled', false).removeClass('disabled');
    }
});

function submitForm(form, event)
{
    event.preventDefault();

    let question = $('input[name=question]:checked').val() === 'riogaleao';

    if(!question) {
        $('#questionRequired').show();
    }

    let inputImage = $('#image');

    if (!inputImage.val()) {
        $('#imageRequired').show();
        $('html,body').animate({ scrollTop: 1000 }, 'slow');
        return;
    }

    if(!allowSubmitForm
        || !inputImage.val()
        || !$(form).valid()
        || !question
        || $('#boughtDate').hasClass('error-custom')
        || $('#receiptValue').hasClass('error-custom')) {

        return;
    }

    let loader = $('.loader');
    loader.show();

    let formData = new FormData($(form)[0]);
    formData.append("totalCouponCount", qtdTotal);
    formData.append("totalValue", valueTotal);
    formData.append("products", JSON.stringify(products));

    if(!jQuery.isEmptyObject( resizedImage )) {
        formData.delete('image');
        formData.append("newImage", resizedImage);
    }

    const url = '/meus-cupons/send-invoice';

    const request  = $.ajax({
        type: "POST",
        url: url,
        data: formData,
        cache: false,
        contentType: false,
        processData: false,
        dataType: "json"
    });

    request.then(function(response) {
        if (response.cod === 200) {
            return $('#dialog').modal('show');
        }

        $('#dialog-fail').modal('show');
    });

    request.catch(function(xhr, status, error) {
        if (xhr.status === 401) {
            $('#dialog-fail .modal-body').html('<p>' + xhr.responseJSON.message + '</p>');
        } else if (xhr.status === 406) {
            $('#dialog-fail .modal-body').html('<p>' + xhr.responseJSON.data.message + '</p>');
        }
        $('#dialog-fail').modal('show');
    });

    request.always(function() {
        loader.show();
    });
}

$("#valueMessage .close").click(function() {
    $("#valueMessage").hide();
});

$("#storeDocumentNumber").change(function() {
    let storeName = '';

    for(let i = 0; i < stores.length; i ++) {
        if(stores[i]['id'] == $(this).val()) {
            storeName = stores[i]['text'].split(' - ')[1];
            i = stores.length;
        }
    }

    if(storeName) {
        $('#storeName').val(storeName);
        $('#boughtDate').focus();
    }


    // let loader = $('.loader');
    // event.preventDefault();
    //
    // loader.show();
    //
    // const request  = $.ajax({
    //     type: "GET",
    //     url: "/search/search-cnpj/" + $(this).val().replace(/\D/g, ''),
    //     cache: false,
    //     contentType: false,
    //     processData: false,
    //     dataType: "json"
    // });
    //
    //
    // request.then(function(response) {
    //     if (response.cod === 200) {
    //         $('#storeName').val(response.data.storeName).attr('readonly', true);
    //         $('#boughtDate').focus();
    //     }
    // });
    //
    // request.catch(function(xhr, status, error) {
    //     $('#storeName').val('').attr('readonly', false);
    // });
    //
    // request.always(function() {
    //     loader.hide();
    // });
});

$('#add-image').click(function(){
    $('#image').trigger('click');
});

$('#close-image-preview').click(function(){
    $('#image').val('');
    $('.previewImage').hide();
    $('#add-image').text('Adicionar imagem');
});

function resetProductSearch()
{
    $("#productSearch").val('').trigger('change').focus();
    $("#quantityNumber").val('');
    $('#btnAddProduct').attr('disabled', true);
    $('#productValue').val('').attr('disabled', true);
}

function getFileExtension(filename) {
    return (/[.]/.exec(filename)) ? /[^.]+$/.exec(filename)[0] : undefined;
}

function getStores()
{
    $('.loader').show();

    let get = $.ajax({
        type: "GET",
        url: '/meus-cupons/get-stores',
        contentType: false,
        processData: false,
        dataType: "json"
    });

    get.done(function (data) {
        if (data.cod !== 200) return;

        stores = data.data;

        $("#storeDocumentNumber").select2({
            placeholder: "Busque pelo CNPJ ou nome da loja da nota",
            data: data.data
        })
    }).always(function(){
        $('.loader').hide();
    });
}

function readURL(obj) {
    var reader = new FileReader();

    reader.onload = function (event) {
        if(obj.size > 2000000) {
            var image = new Image();

            image.onload = function () {
                document.getElementById("image").src = image.src;

                var canvas = document.createElement("canvas");
                var context = canvas.getContext("2d");

                canvas.width = image.width / 4;
                canvas.height = image.height / 4;

                context.drawImage(image,
                    0,
                    0,
                    image.width,
                    image.height,
                    0,
                    0,
                    canvas.width,
                    canvas.height
                );

                $("#previewImage").attr('src', canvas.toDataURL());

                canvas.toBlob(function(blob){
                    resizedImage = blob;
                });
            };

            image.src = event.target.result;
        }else {
            $('#previewImage').attr('src', event.target.result);
        }

        $('.previewImage').show();
    };

    reader.readAsDataURL(obj);

    $('#add-image').text('Alterar imagem');

}

$("#image").change(function() {
    let maxSize = $('#image').data('max-size');
    let fileInput = $('#image');
    let messageFileMax = $('#fileSizeMax');
    let messageImageRequired = $('#imageRequired');
    let messageExtensionInvalid = $('#extensionInvalid');
    let fileObj = fileInput.get(0).files[0];

    if (fileObj) {
        let fileSize = fileObj.size; // in bytes

        if (fileSize > maxSize) {
            messageFileMax.show();
            $('#image').val('');
            return false;
        }
    } else {
        $('#imageRequired').show();
        $('html,body').animate({ scrollTop: $('#add-image').offset().top - 200 }, 'slow');
        return false;
    }

    if (messageFileMax.length) {
        messageFileMax.hide();
    }

    if (messageImageRequired.length) {
        messageImageRequired.hide();
    }

    let extension = null;
    extension = getFileExtension(fileObj.name);

    if (extension.trim() === 'jpg' || extension.trim() === 'png' || extension.trim() === 'jpeg') {

        if (messageExtensionInvalid.length) {
            messageExtensionInvalid.hide();
        }

        readURL(fileObj);
    } else {
        messageExtensionInvalid.show();
        return false;
    }
});

$('#boughtDate').change(function(){
    let elem = $(this);

    removeError(elem);

    if(elem.val() && elem.valid()) {
        $('.loader').show();

        let get = $.ajax({
            type: "POST",
            url: '/meus-cupons/date-campaign-interval',
            data: { date: elem.val() }
        });

        get.done(function (data) {
            if(data) {
                appendError(elem, 'A data está fora do período da campanha');
            }
        }).always(function(){
            $('.loader').hide();
        });
    }
});

$('#receiptValue').change(function(){
    let val = $(this).val();

    removeError($(this));

    if(val) {
        val = parseFloat(val.replace(/\./g,'').replace(/,/g,'.'));

        if(val < 50) {
            appendError($(this), 'O valor mínimo é de 50 reais');
        }
    }
});

function appendError(elem, message)
{
    if(!elem.hasClass('error-custom')) {
        let error = '<label class="error-custom">' + message + '</label>';

        elem.parent('.form-group').append(error);
        elem.addClass('error-custom');
    }
}

function removeError(elem)
{
    if(elem.hasClass('error-custom')) {
        elem.siblings('label.error-custom').remove();

        elem.removeClass('error-custom');
    }
}