window.winnerIndex = null;
window.lineTableInserted = null;
window.lineForm = null;
window.formParams = {};

function onReady() {
    $(".mask-cpf").mask("000.000.000-00");

    onInputChangeEvent();
    registerExpandCampaignEvent();
    registerAddWinnerEvent();
    registerRemoveWinnerEvent();
    registerSaveWinnerEvent();

    confirmSaveWinnerEvent();
    confirmRemoveWinnerEvent();

    removeHighlightWinnerAdded();
}

function onInputChangeEvent() {
    $(".winnerInputColumn").keyup(function() {

        let $allInputs = $(".winnerInputColumn");

        let $emptyInputs = 0;

        for(let i = 0; i < $allInputs.length; ++i) {
            if(!$($allInputs[i]).val()) {
                $emptyInputs += 1;
            }
        }

        if($emptyInputs > 0) {
            $(".btnSaveWinner").attr('disabled', true).css('opacity', 0.3);
        } else {
            $(".btnSaveWinner").removeAttr('disabled').css('opacity', 1);
        }
    });
}

function removeHighlightWinnerAdded()
{
    if($('tr.fadeBackground').length) {
        scrollPage('tr.fadeBackground');
        $('tr.fadeBackground').removeClass('fadeBackground');
    } else {
        scrollPage('.lotteryWinnersContainer.in');
    }
}

function registerExpandCampaignEvent() {
    $(".lotteryWinnersContainer").on('show.bs.collapse', function() {
        let $btnCircle = $(this).prev().find('.btn-circle');
        $btnCircle.html('<i class="fa fa-minus" aria-hidden="true"></i>');
        $btnCircle.addClass('active');
        $btnCircle.parent().parent().find('.lotteryTitle').addClass('highlighted');
    }).on('hide.bs.collapse', function() {
        let $btnCircle = $(this).prev().find('.btn-circle');
        $btnCircle.html('<i class="fa fa-plus" aria-hidden="true"></i>');
        $btnCircle.removeClass('active');
        $btnCircle.parent().parent().find('.lotteryTitle').removeClass('highlighted');
    });
}

function registerAddWinnerEvent()
{
    $(".btnAddWinner").click(function() {
        let $tbody;
        let $parentLine;
        let $table;
        let $lineForm;

        $parentLine = $(this).closest('.lineTable');
        $table = $parentLine.closest('table');

        if($(this).data('first') === 1) {
            $tbody = $parentLine.parent().next();
            $lineForm = $tbody.find("#lineForm");
            $lineForm.detach();
            $tbody.prepend($lineForm);
        } else if($(this).data('index')) {
            $tbody = $parentLine.parent();
            $lineForm = $tbody.find("#lineForm");
            $lineForm.detach();
            $parentLine.after($lineForm);
        }

        if($parentLine.hasClass('lastAddButton')) {
            $(this).parent().hide();
        } else {
            $table.find('.lastAddButton').removeClass('pull-right');
            $table.find('.lastAddButton').show();
        }

        window.winnerIndex = $(this).data('index');
        window.lineForm = $lineForm;
    });
}

function registerRemoveWinnerEvent()
{
    $(".btnRemoveWinner").click(function() {
        if($(this).data('index')) {
            let $parentLine = $(this).parent().parent().parent();

            $(".removeWinnerModal #winnerNameRemove").text($parentLine.find('.winnerName').text());
            $(".removeWinnerModal").modal('show');

            window.winnerIndex = $(this).data('index');
            window.formParams = {
                campaignId: $(this).data('campaign'),
                lineIndex: $(this).data('index')
            }
        }
    });
}

function confirmRemoveWinnerEvent()
{
    $("#formConfirmRemove").click(function() {

        $.post('/adm/remover-ganhador', window.formParams)
            .done(function(response) {
                let urlRedirect = '/adm/ganhadores';
                let campaignId = response.campaignId;

                urlRedirect = campaignId ? urlRedirect + '/' + campaignId : urlRedirect;

                window.location.href = urlRedirect;
            })
            .fail(function(error) {
                $(".removeWinnerModal").modal('hide');
                $("#error").text(error.message).show();
                scrollPage('#error');
            })
            .always(function() {
                window.winnerIndex = null;
                window.lineTableInserted = null;
            });

    });
}

function registerSaveWinnerEvent()
{
    $(".btnSaveWinner").click(function() {
        let $parentLine = $(this).parent().parent().parent();
        let $tbody = $parentLine.parent();
        let $lineForm = $tbody.find("#lineForm");

        let formParams = {};

        let $inputs = $parentLine.find('input');

        for(let i = 0; i < $inputs.length; ++i) {
            let inputName = $($inputs[i])[0].dataset.name;
            formParams[inputName] = $($inputs[i])[0].value;

            $(".saveWinnerModal #" + inputName).text($($inputs[i])[0].value);
        }

        if(window.winnerIndex !== null) {
            formParams['lineIndex'] = window.winnerIndex;
        }

        window.formParams = formParams;
        window.lineTableInserted = $parentLine;
        window.lineForm = $lineForm;

        $(".saveWinnerModal").modal('show');
    });
}

function confirmSaveWinnerEvent()
{
    $("#formConfirmSave").click(function() {

        $.post('/adm/adicionar-ganhador', window.formParams)
            .done(function(response) {
                let urlRedirect = '/adm/ganhadores';

                if('campaignId' in response) {
                    urlRedirect = urlRedirect + '/' + response.campaignId;
                }

                if('index' in response) {
                    urlRedirect = urlRedirect + '/' + response.index;
                }

                window.location.href = urlRedirect;
            })
            .fail(function(error) {
                $(".saveWinnerModal").modal('hide');
                $("#error").text(error.message).show();
                scrollPage('#error');
            })
            .always(function() {
                window.formParams = {};
                window.winnerIndex = null;
                window.lineTableInserted = null;
            });
    });
}

window.scrollPage = function (selector) {
    if($(selector).length) {
        $('html,body').animate({ scrollTop: $(selector).offset().top - 80}, 'slow');
    }
};

$(document).ready(onReady);