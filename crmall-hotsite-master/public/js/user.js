window.allowSubmitForm = false;
window.notAllowedState = false;

window.recaptchaCallback = function () {
    window.allowSubmitForm = true;

    if ($("#acceptPromotionRules").is(":checked")) {
        $('#user-register-send-btn').removeClass('disabled').removeAttr('disabled');
    }
};

window.expiredRecaptchaCallback = function () {
    window.allowSubmitForm = false;
    $('#user-register-send-btn').attr('disabled', true);
    grecaptcha.reset();
};

var validInputs = {
    email: false
};

var userExists = null;

$(document).ready(function () {
    scrollPage('register-container');
    masks();
    validationRules();
    // getOccuptations();
});

function masks() {
    var phoneMask = function phoneMask(phone, e, currentField, options) {
        if (phone.length < 14) {
            return '(00)0000-00009';
        }
        return '(00)00000-0009';
    };

    $(".mask-phone").mask(phoneMask, {
        onKeyPress: function onKeyPress(phone, e, currentField, options) {
            $(currentField).mask(phoneMask(phone), options);
        }
    });

    $(".mask-number").mask("0#");
    $(".mask-cpf").mask("000.000.000-00");
    $(".mask-cnpj").mask("00.000.000/0000-00");
    $(".mask-date").mask("00/00/0000");
    $(".mask-cep").mask("00.000-000");
    $(".money").maskMoney({ thousands: '.', decimal: ',' });
    $('.mask-phone-fix').mask('0000-0000');

    $('.money2').mask('000.000.000.000.000,00', { reverse: true });
}

function validationRules() {
    $('.mask-cpf').rules("add", "cpfBR");
    $('.mask-date').rules("add", "dateITA");
    $(".valid-age").rules("add", "age");
    $(".mask-cnpj").rules("add", "cnpjValidator");
    $("#birthDate").rules("add", "blockFutureDate");
    $(".mask-phone").rules("add", "validPhone");
}

function getOccuptations() {
    var get = $.ajax({
        type: "GET",
        url: '/get-occupations',
        contentType: false,
        processData: false,
        dataType: "json"
    });

    $('.loader').removeClass('hide');

    get.done(function (data) {
        var occupations = [];

        for (var i in data) {
            occupations.push({
                'id': data[i],
                'text': data[i]
            });
        }

        $("#occupation").select2({
            placeholder: "Profissão",
            data: occupations,
            language: {
                "noResults": function noResults() {
                    return "Nenhum resultado foi encontrado.";
                }
            }
        });
    }).always(function () {
        $('.loader').addClass('hide');
    });
}

$("input[name=cep]").change(function () {
    var cep = $(this).val().replace(/\./g, "").replace(/\-/g, "");

    $('.loader').removeClass('hide');

    var get = $.ajax({
        type: "GET",
        url: '/search/cep/' + cep,
        contentType: false,
        processData: false,
        dataType: "json"
    });

    get.done(function (data) {
        if (data.cod !== 200) return;

        var address = data.data;
        populateAddress(address);
        $('.loader').addClass('hide');
    });

    get.fail(function () {
        $('.loader').addClass('hide');
    });
});

function populateAddress(address) {
    $("input[name='streetName']").val(address.streetName).trigger('focus');
    $("input[name='neighborhood']").val(address.neighborhood).trigger('focus');
    $("input[name='city']").val(address.city).trigger('focus');
    $("select[name='state']").val(address.state).trigger('focus');

    if (address.streetName) {
        $("input[name='number']").focus();
    } else {
        $("input[name='streetName']").focus();
    }
}

$("#user-new").submit(function (e) {
    $('.loader').removeClass('hide');

    if (!window.allowSubmitForm || !$(this).valid() || !validInputs.email) {
        e.preventDefault();
        $('.loader').addClass('hide');
        Ladda.stopAll();
    }
});

$("#loginUserForm, #editUser").submit(function (e) {
    if (!$(this).valid() || !validInputs.email) {
        e.preventDefault();
        $('.loader').addClass('hide');
        Ladda.stopAll();
    }
});

$('input[name=cpf],input[name=birthDate]').change(function () {
    var documentNumber = $('input[name=cpf]');
    var birthDate = $('input[name=birthDate]');

    if (birthDate.val() && documentNumber.val() && birthDate.valid() && documentNumber.valid()) {
        $('.loader').removeClass('hide');

        $.ajax({
            type: "GET",
            url: '/search/search-cpf/' + documentNumber.val().replace(/\D/g, '') + '/' + birthDate.val().replace(/\/+/g, '-'),
            cache: false,
            dataType: "json",
            success: function success(data) {
                if (data.cod === 200) {
                    if (data.data.name) {
                        $('input[name=personName]').val(data.data.name);
                    }
                }

                $('.loader').addClass('hide');
            },
            error: function error() {
                $('.loader').addClass('hide');
            }
        });
    }
});

function disabledSubmit() {
    if ($('#acceptPromotionRules').is(":checked") && window.allowSubmitForm) {
        $('#user-register-send-btn').removeClass('disabled').removeAttr('disabled');
        Ladda.bind('.ladda-button:not([disabled])');
        Ladda.bind('.ladda-sleep:not([disabled])', { timeout: 4000 });
    } else {
        $('#user-register-send-btn').addClass('disabled').attr('disabled', true);
    }
}

$('#acceptPromotionRules').change(function () {
    disabledSubmit();
});

$('input[name=cpf]').change(function () {
    if ($(this).valid()) {
        var cpf = $(this);

        $('#message-save-user').hide();
        $('#message-save-user .message').html('');

        $('.loader').removeClass('hide');

        userExists = null;

        $.ajax({
            type: "POST",
            url: '/search/check-cpf',
            data: {
                cpf: cpf.val(),
                cnpj: $('#cnpj').val()
            },
            dataType: "json",
            success: function success(data) {
                if (data.cod === 200 && data.data !== false) {
                    userExists = data.data;
                }

                $('.loader').addClass('hide');
            },
            error: function error(jqXHR, exception) {
                $('.loader').addClass('hide');
            }
        });
    }
});

$('input[name=email]').change(function () {
    var emailElem = $(this);

    removeError(emailElem);

    if (userExists && userExists.recoveryEmail && emailElem.val().trim() === userExists.recoveryEmail.trim()) {
        validInputs.email = true;
    } else if ($(this).valid()) {
        $('.loader').removeClass('hide');

        $.ajax({
            type: "POST",
            url: '/search/email-exists',
            data: { "email": emailElem.val(), "cpf": $("#cpf").val() },
            dataType: "json",
            success: function success(data) {
                validInputs.email = !data.data;

                if (validInputs.email) {
                    removeError(emailElem);
                } else {
                    appendError(emailElem, 'Email já cadastrado');
                }

                $('.loader').addClass('hide');
            },
            error: function error(jqXHR, exception) {
                appendError(emailElem, 'Email já cadastrado');
                $('.loader').addClass('hide');
            }
        });
    }
});

function appendError(elem, message) {
    if (!elem.hasClass('error-custom')) {
        var error = '<label class="error-custom">' + message + '</label>';

        elem.parent('.form-group').append(error);
        elem.addClass('error-custom');
    }
}

function removeError(elem) {
    if (elem.hasClass('error-custom')) {
        elem.siblings('label.error-custom').remove();

        elem.removeClass('error-custom');
    }
}

function checkSurvey() {
    var elems = $('.surveyAnswerInput');

    if (elems.length === 0) {
        return true;
    }

    return $('.surveyAnswerInput:checked').length > 1;
}

$('#cancel-button').click(function (e) {
    e.preventDefault();

    var r = confirm("Tem certeza que deseja cancelar!");

    if (r === true) {
        window.location.href = '/';
    }
});