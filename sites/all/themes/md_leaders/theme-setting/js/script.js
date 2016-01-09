(function($){
    $(window).load(function(){

/////////////////////////////////////////////// JQUERY UI TABS ////////////////////////////////////////////////////////
        var tabCookieName = "maintabs";
        var subTab1CookieName = "subtabs1";
        var subTab2CookieName = "subtabs2";
    	$(function() {
            // Save cookie for each tab group, each tab group need unique cookie name
            $("#md-framewp-body").tabs({
                active : ($.cookie(tabCookieName) || 0),
                activate : function( event, ui ) {
                    var newIndex = ui.newTab.parent().children().index(ui.newTab);
                    $.cookie(tabCookieName, newIndex, { expires: 1 });
                }
            });
            $( "#md-general, #md-design, #md-display, #md-text-typography,#md-code,#md-config").tabs({
                active : ($.cookie(subTab1CookieName) || 0),
                activate : function( event, ui ) {
                    var newIndex = ui.newTab.parent().children().index(ui.newTab);
                    $.cookie(subTab1CookieName, newIndex, { expires: 1 });
                }
            });
            $(".md-subtabs").tabs({
                active : ($.cookie(subTab2CookieName) || 0),
                activate : function( event, ui ) {
                    var newIndex = ui.newTab.parent().children().index(ui.newTab);
                    $.cookie(subTab2CookieName, newIndex, { expires: 1 });
                }
            })
		});

/////////////////////////////////////////////// ADD CLASS TO ALL BUTTON ////////////////////////////////////////////////
        $("input[type='submit'],a.button").addClass("md-button");
    /*========== Scroll bar ==========
        $(".md-content-main").mCustomScrollbar({
        	mouseWheel: true,
        	autoDraggerLength:true,
        	scrollInertia: 200,
        	autoHideScrollbar: true
        }); 
    */

    /*========== Script ON-OFF , ENABLE - DISABLEr ==========*/
        $(".click-disable").on("click",function(){
            $(this).parent().addClass("selected");
        });
        $(".click-enable").on("click",function(){
            $(this).parent().removeClass("selected");
        });

///////////////////////////////////////////////// JQUERY UI SlIDER RANGE /////////////////////////////////////////////////
//        $(".slider-range").each(function(){
//            var $self = $(this),
//                id = $(this).attr('id'),
//                max = $(this).attr('data-max'),
//                min = $(this).attr('data-min'),
//                value = $(this).attr('data-value');
//            // Append an element to make it slider range
//            $(this).parent().parent().append("<div id='"+id+"-slider-range'></div>");
//            // Call jquery slider ui
//            $("#"+id+"-slider-range").slider({
//                range: "min",
//                value: value,
//                min: min,
//                max: max,
//                slide: function( event, ui ) {
//                    $self.val( ui.value );
//                }
//            });
//            // Put value of slider range into input
//            $self.val($( "#"+id+"-slider-range" ).slider( "value" ));
//        });
/////////////////////////////////////////////// CHOOSE AND PREVIEW FONTS ///////////////////////////////////////////////
        $(".choosefont").choosefont();

    /*========== Slides Accordion ==========*/

        $( ".md-accordion-item .md-field" ).accordion({
            collapsible: true,
            active: false 
        });

    /*========== Drag and Drop ==========*/
        $( "#md-block-enabled, #md-block-disabled, #md-block-backup" ).sortable({
            placeholder: "placeholder",
            revert: true
        });
        $( "#md-block-enabled, #md-block-disabled, #md-block-backup" ).disableSelection();
//////////////////////////////////////////////////// Color Picker /////////////////////////////////////////////////////
        $(".form-colorpicker").spectrum({
            showAlpha: true,
            showInput: true,
            allowEmpty:true,
            showInitial: true,
            preferredFormat: "hex3"
        })
//////////////////////////////////////////////////// Add Class To Default Submit /////////////////////////////////////////////////////
        $("#md-framewp-footer .form-actions #edit-submit").addClass("btn btn-save");
    })
})(jQuery);
    ////////////////////////////////////////////////////// Add more content ////////////////////////////////////////////////
    (function($){
        // Define each preview wrapper
        var baseUrl = Drupal.settings.baseUrl,
            container,
            click,
            working,
            preview,
            multi = false,
            id,
            dataid,
            sortable,
            order,
            target,
            action,
            prepareWrap,
            clickMedia,
            popup,
            number,
            newnum,
            maxnum,
            str,
            newstr,
            hiddenOrder,
            hiddenNum,
            data = new Array(),
            wrapItem = $('<li class="draggable-item sortable-item toggle-item"></li>'),
            returnData;
        jQuery(document).ready(function(){
            // First Push number of each content to array
//            for(var i=1;i<=4;i++){
//                data["pr_"+i+"_skills_preview"] = [];
//                $("#pr_"+i+"_skills_preview").find("li.sortable-item").each(function(){
//                    data["pr_"+i+"_skills_preview"].push(parseInt($(this).attr("data-num"),10));
//                });
//                if(data["pr_"+i+"_skills_preview"].length <=1 ) {
//                    $("#pr_"+i+"_skills_preview").find(".md-remove").hide();
//                }
//
//            }
//            data["hd_image_slide_preview"] = [];
//            $("#hd_image_slide_preview").find("li.sortable-item").each(function(){
//                data["hd_image_slide_preview"].push(parseInt($(this).attr("data-num"),10));
//            });
//            if(data["hd_image_slide_preview"].length <=1 ) {
//                $("#hd_image_slide_preview").find(".md-remove").hide();
//            }
//            data["hd_slide_preview"] = [];
//            $("#hd_slide_preview").find("li.sortable-item").each(function(){
//                data["hd_slide_preview"].push(parseInt($(this).attr("data-num"),10));
//            });
//            if(data["hd_slide_preview"].length <=1 ) {
//                $("#hd_slide_preview").find(".md-remove").hide();
//            }
//            data["hd_pt_slide_preview"] = [];
//            $("#hd_pt_slide_preview").find("li.sortable-item").each(function(){
//                data["hd_pt_slide_preview"].push(parseInt($(this).attr("data-num"),10));
//            });
//            if(data["hd_pt_slide_preview"].length <=1 ) {
//                $("#hd_pt_slide_preview").find(".md-remove").hide();
//            }

            data["hdsocial_info_preview"] = [];
            $("#hdsocial_info_preview").find("li.sortable-item").each(function(){
                data["hdsocial_info_preview"].push(parseInt($(this).attr("data-num"),10));
            });
            if(data["hdsocial_info_preview"].length <=1 ) {
                $("#hdsocial_info_preview").find(".md-remove").hide();
            }

            data["highlights_info_preview"] = [];
            $("#highlights_info_preview").find("li.sortable-item").each(function(){
                data["highlights_info_preview"].push(parseInt($(this).attr("data-num"),10));
            });
            if(data["highlights_info_preview"].length <=1 ) {
                $("#highlights_info_preview").find(".md-remove").hide();
            }


            data["hd_ico_preview"] = [];
            $("#hd_ico_preview").find("li.sortable-item").each(function(){
                data["hd_ico_preview"].push(parseInt($(this).attr("data-num"),10));
            });
            if(data["hd_ico_preview"].length <=1 ) {
                $("#hd_ico_preview").find(".md-remove").hide();
            }

            data["ft_social_preview"] = [];
            $("#ft_social_preview").find("li.sortable-item").each(function(){
                data["ft_social_preview"].push(parseInt($(this).attr("data-num"),10));
            });
            if(data["ft_social_preview"].length <=1 ) {
                $("#ft_social_preview").find(".md-remove").hide();
            }
            data["contact_info_preview"] = [];
            $("#contact_info_preview").find("li.sortable-item").each(function(){
                data["contact_info_preview"].push(parseInt($(this).attr("data-num"),10));
            });
            if(data["contact_info_preview"].length <=1 ) {
                $("#contact_info_preview").find(".md-remove").hide();
            }
            // Sortable all element needed
            $(".sortable").sortable({
                create: function() {
                    order = $(this).sortable('toArray');
                    $(this).parent().parent().parent().parent().find(".hidden-order").val(order.join('|'));
                },
                update: function() {
                    order = $(this).sortable('toArray');
                    $(this).parent().parent().parent().parent().find(".hidden-order").val(order.join('|'));
                },
                scrollSpeed: 120,
                cursor: "move",
                opacity: 0.5,
                scrollSensitivity: 10
            });

            selectMedia();
            /* Load Icon Dialog Fake Markup */
            var icFake = Drupal.settings.icFake;
            loadIcon(null);
            iconDialog();
            clickIcon();
            clickAdd();
            removeObj();


            function createPop() {
                $("#popup-"+id).dialog({
                    title: action+" Dialog",
                    modal:true,
                    resizable: false,
                    draggable: false,
                    width: 800,
                    height: 400,
                    autoOpen:false,
                    position: [($(window).width()-800)/2, ($(window).height()-400)/2],
                    open: function() {
                        openPop();
                        $(this).find("input.form-submit").hide(); // Hide edit and remove button
                    },
                    close: function() {
                        closePop();
                    },
                    buttons: [{
                        text: "Done",
                        click: function() {
                            finishPop();
                            $(this).dialog( "close" ); // Close dialog
                            $(this).dialog("destroy").remove();
                        }
                    }]
                });
            }
            function clickAdd() {
                // Add more object
                $('.add-more').unbind("click").click(function(event){
                    action = 'add';
                    container = $(this).parent().parent(); // Working object for this type action
                    sortable = container.find(".sortable");
                    working = $(this).parent().parent().find(".data-container").attr("id");
                    hiddenOrder = container.find(".hidden-order"); // Hidden sort order data
                    hiddenNum = container.find(".hidden-num");
                    $(this).attr("data-max-num",Math.max.apply(Math, data[working])); // Push max number for get correct content
                    number = parseInt($(this).attr("data-max-num"),10);
                    newnum = number+1;
                    click = $(this);
                    target = $(this).attr("href");
                    preview = $("#"+$(this).attr("data-preview"));
                    popup = preview.find(".popup-wrapper");
                    id = target.substr(1);
                    str = new RegExp("no"+number,'g'); // Current number
                    newstr = "no"+newnum; // New number
                    prepareWrap = $("[data-id="+id+"]").clone(); // Get new html with new number
                    prepareWrap.find("input.form-text").each(function(){
                        $(this)[0].setAttribute("value",""); // set current value
                    });
                    var html = prepareWrap.html().replace(str,newstr);
                    prepareWrap.html('<li data-id="'+id.replace(str,newstr)+'" data-num="'+newnum+'" class="draggable-item sortable-item toggle-item">'+html+'</li>'); // Prepare new html
                    preview.find(".sortable").append($('<li id="'+id.replace(str,newstr)+'" data-id="'+id.replace(str,newstr)+'" data-num="'+newnum+'" class="draggable-item sortable-item toggle-item">'+html+'</li>')); // Append to preview
                    data[working].push(newnum);
                    click.attr('data-max-num',Math.max.apply(Math, data[working])); //  Change max num
                    click.attr('href',target.replace(str,newstr)); // Change click target
                    // Build new sort for new element
                    var newSort = $(sortable);
                    $(newSort).sortable({
                        update: function() {
                            order = $(this).sortable('toArray');
                            hiddenOrder.val(order.join('|'));
                            console.log(order)
                        },
                        create: function( event, ui ) {
                            order = $(this).sortable('toArray');
                            hiddenOrder.val(order.join('|'));
                        },
                        scrollSpeed: 120
                    });
                    // Call select media function
                    order = $(newSort).sortable('toArray');
                    console.log(order);
                    hiddenOrder.val(order.join('|'));
                    hiddenNum.val(Math.max.apply(Math, data[working]));

                    preview.find(".md-remove").show();
                    loadIcon($("#"+id.replace(str,newstr)));

                    removeObj();
                    event.preventDefault();
                });
            }
            function removeObj() {
                $(".md-remove").unbind("click").click(function(event){
                    // Need to remove from number data array
                    container = $(this).parent().parent().parent().parent().parent();
                    sortable = container.find(".sortable");
                    working = container.attr("id");
                    click = container.parent().find('.add-more');
                    hiddenOrder = container.find(".hidden-order"); // Hidden sort order data
                    hiddenNum = container.find(".hidden-num");
                    console.log(data[working]);
                    var index = data[working].indexOf(parseInt($(this).parent().attr("data-num"),10));
                    if(index > -1){
                        data[working].splice(index,1);
                    }
                    var currId = $(this).parent().attr("data-id");
                    var newHref = currId.replace("no"+parseInt($(this).parent().attr("data-num"),10),"no"+Math.max.apply(Math, data[working]));
                    console.log(data[working]);
                    if(data[working].length <=1) {
                        container.find(".md-remove").hide();
                    }
                    click.attr('data-max-num',Math.max.apply(Math, data[working])); // New max num for click object
                    click.attr('href',"#"+newHref); // New click target

                    $(this).parent().remove(); // Remove object
                    var newSort = $(sortable);
                    $(newSort).sortable({
                        update: function() {
                            order = $(this).sortable('toArray');
                            hiddenOrder.val(order.join('|'));
                            console.log(order);
                        },
                        create: function( event, ui ) {
                            order = $(this).sortable('toArray');
                            hiddenOrder.val(order.join('|'));
                        }
                    });
                    order = $(newSort).sortable('toArray');
                    console.log(order);
                    hiddenOrder.val(order.join('|'));
                    hiddenNum.val(Math.max.apply(Math, data[working]));
                    event.preventDefault();
                });
            }
            function updateSortable(newSort) {
                $(newSort).sortable({
                    update: function() {
                        order = $(this).sortable('toArray');
                    },
                    create: function( event, ui ) {
                        order = $(this).sortable('toArray');
                    },
                    scrollSpeed: 120

                });
                $(newSort).bind( "sortupdate", function( event, ui ) {
                    order = $(this).sortable('toArray');
                } );

            }
            function selectMedia() {
                $(document).on('click', ".select-media",function(event){
                    clickMedia = $(this);
                    Drupal.media.popups.mediaBrowser(chooseBackground);
                    event.preventDefault();
                })
            }
            chooseBackground = function(selected) {
                clickMedia.prev().find("img").attr("src", selected[0].url).trigger("change");
                clickMedia.next().val(selected[0].fid);
            }
            function finishPop() {
                if(action == "add") {
                    addObj();
                } else {
                    editObj();
                }
                updateSortable();
                clickAdd();
                removeObj();
            }
/////////////////////////////////////////////////// Icon Picker ////////////////////////////////////////////////////////

            function loadIcon(Obj) {
                if(Obj == null) {
                    $(".icon-picker").each(function(){
                        var $self = $(this),
                            realWrap = $self.find("fieldset:first-child"),
                            title = $self.find(".fieldset-title").text().replace("Hide",""),
                            id = realWrap.find("select").attr("id");
                        var optSelect = $("#"+id).find("option:selected");
                        var arrIconValue = optSelect.val().split("|");
                        /* Wrap some html and prepare fake icon select */
                        $self.append('<div class="icon-wrapper">' +
                            '<span><h4>'+title+'</h4></span>' +
                            '<a class="icon-dialog-open" data-id="'+id+'-fake" href="#"><div class="icon-preview"><i class="'+arrIconValue[0]+'  '+arrIconValue[1]+'"></i></div></a>' +
                            '</div><div id="'+id+'-fake" class="icon-markup">'+icFake+'</div>');
                        /* Hide real select */
                        realWrap.hide();
                        /* Create dialog */
                        $("#"+id+"-fake").dialog({
                            draggable: false,
                            autoOpen: false,
                            modal: true,
                            width: "80%",
                            minHeight: 400,
                            resizable: false,
                            dialogClass: "icon-dialog",
                            title: "Icon Picker Dialog"
                        })
                    });
                } else {
                    var realWrap = Obj.find(".icon-picker fieldset:first-child"),
                        id = realWrap.find("select").attr("id");
                    Obj.find(".icon-dialog-open").attr("data-id",""+id+"-fake");
                    Obj.find(".icon-wrapper").append('<div id="'+id+'-fake" class="icon-markup">'+icFake+'</div>');
                    console.log(id);
                    /* Create dialog */
                    $("#"+id+"-fake").dialog({
                        draggable: false,
                        autoOpen: false,
                        modal: true,
                        width: "80%",
                        minHeight: 400,
                        resizable: false,
                        dialogClass: "icon-dialog",
                        title: "Icon Picker Dialog"
                    })
                }
                iconDialog();
                clickIcon();

            }


            /* Open dialog */
            function iconDialog () {
                $(".icon-dialog-open").unbind('click').click(function(){
                    /* Get id to open dialog */
                    var id = $(this).attr("data-id");
                    console.log(id);
                    $("#"+id).dialog("open");
                    return false;
                });
            }

            /* Fake Icon click event */
            function clickIcon() {
                $(".fake-icon").unbind('click').click(function(){
                    /* Get select id */
                    var id = $(this).parent().parent().parent().attr("id").replace("-fake",""),
                        $select = $("#"+id),
                        iconValue = $(this).attr("data-icon"),
                        iconName = $(this).attr("icon-name"),
                        iconBundle = $(this).attr("data-bundle"),
                        newIcon = '<i class="'+iconBundle+' '+iconName+'"></i>';
                    /* Replace icon preview*/
                    $select.parent().parent().parent().parent().parent().find('.icon-preview').html(newIcon);
                    /* Replace icon value in select */
                    $select.find('option[value="'+iconValue+'"]').attr('selected',true);
                    $("#"+id+"-fake").dialog("close");
                    return false;
                })
            }

			/* Media popup click event */
            $(document).delegate(".media-select-button",'click',function(event){
                var mediaWrapper = $(this).parents(".md-media-wrapper");
                Drupal.media.popups.mediaBrowser(function(files) {
                    var file = files[0],
                        inputVal = {"fid":file.fid,"url":file.url};
                    console.log(file);
                    $("div.preview", mediaWrapper).html('<img alt="" class="img-preview" src="' + file.url + '" />');
                    $("input.media-hidden-value", mediaWrapper).val(JSON.stringify(inputVal));

                });
                event.preventDefault();
            })

        })

})(jQuery);

