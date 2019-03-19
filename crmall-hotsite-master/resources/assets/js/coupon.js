function onReady()
{
    let validator = null;
    let sendButton = $('#send-button');

    let validInvoice = false;

    $('#acceptPromotionRules').change(function () {
        if ($(this).is(":checked")) {
            $('#send-button').removeClass('disabled').attr('disabled', false);
        } else {
            $('#send-button').addClass('disabled').attr('disabled', true);
        }
    });

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

        $.validator.addMethod('dateValidCampaign', function(value) {

            let returnValue = false;

            $.ajax({
                type: 'POST',
                url: '/meus-cupons/date-campaign-interval',
                data: { date: $( "#boughtDate" ).val() },
                success: function(response) {
                    returnValue = !response;
                },
                dataType: 'json',
                async: false
            });

            return returnValue;
        }, 'Data inválida para o período da Campanha!');

        $.validator.messages.required = 'Campo obrigatório';

        $.validator.addMethod("invoiceDuplicated", function (value, element) {
            if (!validInvoice && $("#storeDocumentNumber").val()) {
                $.ajax({
                    type: "GET",
                    url: '/meus-cupons/check-duplicated-invoice?code=' + value + '&storeDocument=' + $("#storeDocumentNumber").val(),
                    async: false,
                    success: function (response) {
                        validInvoice = !response.data.duplicated;
                    },
                    error: function (jqXHR, exception) {
                        console.log(jqXHR);
                    }
                });

                let returnValid = validInvoice;
                validInvoice = false;

                return returnValid;
            }

            return true;
        }, "Nota já cadastrada.");

        $.validator.addMethod("cnpj", function (value, element) {

            var numeros, digitos, soma, i, resultado, pos, tamanho, digitos_iguais;
            if (value.length == 0) {
                return false;
            }

            value = value.replace(/\D+/g, '');
            digitos_iguais = 1;

            for (i = 0; i < value.length - 1; i++)
                if (value.charAt(i) != value.charAt(i + 1)) {
                    digitos_iguais = 0;
                    break;
                }
            if (digitos_iguais)
                return false;

            tamanho = value.length - 2;
            numeros = value.substring(0, tamanho);
            digitos = value.substring(tamanho);
            soma = 0;
            pos = tamanho - 7;
            for (i = tamanho; i >= 1; i--) {
                soma += numeros.charAt(tamanho - i) * pos--;
                if (pos < 2)
                    pos = 9;
            }
            resultado = soma % 11 < 2 ? 0 : 11 - soma % 11;
            if (resultado != digitos.charAt(0)) {
                return false;
            }
            tamanho = tamanho + 1;
            numeros = value.substring(0, tamanho);
            soma = 0;
            pos = tamanho - 7;
            for (i = tamanho; i >= 1; i--) {
                soma += numeros.charAt(tamanho - i) * pos--;
                if (pos < 2)
                    pos = 9;
            }

            resultado = soma % 11 < 2 ? 0 : 11 - soma % 11;

            return (resultado == digitos.charAt(1));
        }, "Informe um CNPJ válido");

        validator = $('#invoice-form').validate({
            rules: {
                date: {
                    brDate: true,
                    blockFutureDate: true,
                    dateValidCampaign: true
                },
                code: { invoiceDuplicated: true },
                storeDocumentNumber: { cnpj: true }
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

    function submitForm(form, event)
    {
        event.preventDefault();

        sendButton.prop('disabled', true);

        if (!$(form).valid()) {
            sendButton.prop('disabled', false);
            return;
        }

        $('.loader').removeClass('hide');

        const url = '/meus-cupons/send-invoice';
        const request = $.post(url, $(form).serialize());

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
            sendButton.prop('disabled', false);
            $('.loader').addClass('hide');
        });
    }

    maskElements();
    validation();
    scrollPage('register-coupon-container');

    $("#storeDocumentNumber, #boughtDate").change(function() {
        var $code = $("#code");

        if($code.val()) {
            $code.valid();
        }
    });
}

$(document).ready(onReady);