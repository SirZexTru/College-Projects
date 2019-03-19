$.validator.addMethod('blockFutureDate', function(value) {
    return !(moment(value, 'DD/MM/YYYY', true) > moment());
}, 'A data é maior que a data de hoje');

$.validator.addMethod('age', function (value) {
    value = value.split('/');
    value = value[2] + '-' + value[1] + '-' + value[0];

    var birthDate = new Date(value);
    var age = ~~((Date.now() - birthDate) / (31557600000));

    return age >= 18;
}, 'Precisa-se ter mais de 18 anos para participar');

$.extend($.validator.messages, {
    required: "Este campo &eacute; obrigat&oacute;rio.",
    cpfBR: "Digite um CPF válido"
});

$.validator.addMethod('validPhone', function(value) {
    return value.length >= 13;
}, 'Telefone inválido');