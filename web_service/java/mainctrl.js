(function ($){
$.extend($.mainctrl,{
  extend : function(methods) {
    $.extend($.fn.mainctrl,methods);
  },
  getAccessor : function(obj,expr) {
    var ret,p,prm = [], i;
    if( typeof expr === 'function') { return expr(obj); }
    ret = obj[expr];
    if(ret===undefined) {
      try {
        if ( typeof expr === 'string' ) {
          prm = expr.split('.');
        }
        i = prm.length;
        if( i ) {
          ret = obj;
            while (ret && i--) {
            p = prm.shift();
            ret = ret[p];
          }
        }
      } catch (e) {}
    }
    return ret;
  }
})  
$.fn.mainctrl = function(pin) {
  if (typeof pin == 'string') {
    var fn = $.mainctrl.getAccessor($.fn.mainctrl,pin);
    if (!fn) {throw ("No such method: " + pin);}
    var args = $.makeArray(arguments).slice(1);
    return fn.apply(this,args);
  }
  return this.each(function(){
    var this_obj = $(this);
    var usinfo = pin.usinfo;
    var FID = usinfo.USFID;
    var current_stage = pin.init_trigger;
    var prevent_history_recall = 0;
    var preID = {};
    console.log(pin)
    
    
    
    
    
    var server_comm = 
    {
      
      send_auth_mail:function(e)
      {
        server_exchange("server_comm/send_auth_mail",{uid:e.data.uid},function(){
          console.log(this)
        },function(){
          //window.location = "";
        });
      },
      save_material:function(info_obj,role_id,callback,type)
      {
        var error_cnt = 0;
        var savedata = {};
        var value_array = {};
        var delete_item = {};
        info_obj.find(".error").removeClass("error");
        info_obj.find(".field_value").each(function(i,o){
          var name = $(o).attr("name");
          var value = $.trim($(o).val());
          value_array[name] = value;
          var valid = ui_ctrl.validation($(o));
          if(valid===false)error_cnt++;
        })
        if(error_cnt){
          if(role_id){
            var section_id = info_obj.find(".inputframe.error").eq(0).parents(".navi-detail-frame")[0].id;
            this_obj.find(".navi-detail-frame").hide().end().find(".navi-detail-frame#"+section_id).show();
            this_obj.find(".d-navi-tabs").removeClass('active').end().find(".d-navi-tabs#"+section_id).addClass('active');
          }
          $("body,html").scrollTop(info_obj.find(".inputframe.error").eq(0).offset().top);
          if(typeof(callback) === 'function')callback.call(false);
          return false;
        }
        savedata["general"] = value_array;
        loading_animation();
        type = type==undefined?"":type;
        var server_address_prefix = "server_comm/add_material/";
        if(type)server_address_prefix = "server_comm/update_material/";
        server_exchange(server_address_prefix+current_stage,{FID:FID,savedata:savedata,delete_item:delete_item,tid:role_id,type:type},function(){
          //console.log(this)
          for(var i in this.rtn)this_obj.find(".summary-txt-frame span.txt#"+i).text(this.rtn[i]);
          this_obj.find(".field_value").each(function(i,o){$(o).attr("pre_v",$(o).val());})
//          if(this.new_userid){server_comm.sendauthmail({uid:this.new_userid},1)}
          if(typeof(callback) === 'function')callback.call(this);
        },function(){
          //console.log(this)
          //window.location = "";
        });
      },
    }
    var ui_ctrl = 
    {
      Num_Input_Mask:function(e)
      {
        var keynum = e.which;if (typeof keynum =='undefined')keynum = e.keyCode;
        if(keynum&&keynum!=8&&(keynum<48||keynum>57)) return false;
      },
      Float_Input_Mask:function(e)
      {
        var float_length = parseInt($(this).attr("fl")) - 1;
        var keynum = e.which;
        var ctl = this;
        var startPos = ctl.selectionStart;
        var endPos = ctl.selectionEnd;
        var point_position = $(this).val().indexOf(".",0);
        if (typeof keynum =='undefined')keynum = e.keyCode;
        var keychar = String.fromCharCode(keynum);
        if (point_position!=-1) {
          if(keynum==46) return false;
          var float_num = $(this).val().substr(point_position+1); 
          if(float_num.length>float_length&&(startPos>point_position))return false;       
        }else {if (keynum==46&&$(this).val()=="") return false;}
        if ($(this).val().indexOf("0",0)==0) {
          if ((point_position==-1)&&keynum!=46&&startPos==endPos) return false;
        }  
        if(keynum==46||keynum==27||keynum==8||e.ctrlKey||e.altKey||e.metaKey||keynum<32) return true; // ignore  . esc backspace delete special key space
        return /\d/.test(keychar) || /\t/.test(keychar);
      },
      validation:function(input){
        var result = true;
        var value = $.trim(input.val());
        if(input.hasClass('req')&&value==""){result = false;}
        if(input.attr('type')=="email"&&value)
          if (!(/^((([a-z]|\d|[!#\$%&'\*\+\-\/=\?\^_`{\|}~]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])+(\.([a-z]|\d|[!#\$%&'\*\+\-\/=\?\^_`{\|}~]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])+)*)|((\x22)((((\x20|\x09)*(\x0d\x0a))?(\x20|\x09)+)?(([\x01-\x08\x0b\x0c\x0e-\x1f\x7f]|\x21|[\x23-\x5b]|[\x5d-\x7e]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(\\([\x01-\x09\x0b\x0c\x0d-\x7f]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]))))*(((\x20|\x09)*(\x0d\x0a))?(\x20|\x09)+)?(\x22)))@((([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.)+(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.?$/i.test(value))) {
            result = false;
          }
        if(input.hasClass('dob')&&value){
          var time = new Date(value).getTime();
          var now = new Date().getTime();
          if(!(/^[12][90][0-9][0-9]\/[01]?[0-9]\/[0-3]?[0-9]$/).test(value))result = false;
          else if(time>now){result = false;}
          else if(isNaN(time)){result = false;}
        }
        if(result===false)input.parents(".inputframe").addClass("error");
        return result;
      },
      check_items:function(e)
      {
        if(e.stopPropagation){e.stopPropagation();}else{e.cancelBubble = true;}
        var obj = $(this);
        var parent_obj = obj.parents(".inputframe");
        var keynum = null;
        if(e.type=="keydown"){
          var keynum = e.which;if (typeof keynum =='undefined')keynum = e.keyCode;
          if(keynum==32)e.preventDefault();
        }
        if(keynum==32||keynum==13||e.type=="click"){
          if(obj.hasClass("checked")){obj.removeClass("checked");parent_obj.find("input.check").val("");}
          else{
            parent_obj.find(".chk_frame").removeClass("checked").end().find("input.check").val(obj.attr("val"));
            obj.addClass("checked");
          }
        }
        if(parent_obj.find("input.check").val()!=parent_obj.find("input.check").attr("pre_v"))this_obj.find(".info-save").addClass('active');
      },
      dd_ctrl:function(e)
      { 
        if(e.stopPropagation){e.stopPropagation();}else{e.cancelBubble = true;}
        var obj = $(this);
        var parent_obj = obj.parent();
        if(this.prevevent!=e.type){
          if(parent_obj.hasClass("opened")&&this.prevevent=="focus"&&e.type=="click")return false;
        }
        if(e.isTrigger&&parent_obj.hasClass("closed"))return true;
        if(parent_obj.hasClass("opened")){
          parent_obj.find("ul").slideUp(100,function(){
            parent_obj.removeClass("opened").addClass("closed");
          })
        }
        if(parent_obj.hasClass("closed")){
          parent_obj.find("ul").slideDown(100,function(){
            parent_obj.removeClass("closed").addClass("opened");
          })
        } 
        this.prevevent = e.type;
      },
      select_items:function(e)
      {
        if(e.stopPropagation){e.stopPropagation();}else{e.cancelBubble = true;}
        var obj = $(this);
        var keynum = null;
        if(e.type=="keydown"){
          var keynum = e.which;if (typeof keynum =='undefined')keynum = e.keyCode;
          if(keynum==32)e.preventDefault();
        }
        obj.parents(".ddframe").find("input").val(obj.attr("rep")).prev().text(obj.text());
        if(obj.parent().hasClass('withother')&&!obj.hasClass('otherlink')){
          obj.parents('div.input').find("input.other_dd_text").val("");
        }
        if(obj.parents(".ddframe").find("input").val()!=obj.parents(".ddframe").find("input").attr("pre_v"))this_obj.find(".info-save").addClass('active');
        obj.parents(".ddframe").find("span.ddind").focus();
        obj.parent().slideUp(100,function(){$(this).parents(".ddframe").removeClass("opened").addClass("closed").find("span.ddind").focus();})
      },
      bind_input_event:function(tmphtml)
      {
        tmphtml.find(".field_value").each(function(i,o){$(o).attr("pre_v",$(o).val());});
        tmphtml.find(".ddframe span.ddind").bind("click focus",ui_ctrl.dd_ctrl);
        tmphtml.find(".ddframe a").bind("mouseover",function(){$(this).parent().find("a.select").removeClass("select");$(this).addClass("select");});
        tmphtml.find(".ddframe a").bind("click",ui_ctrl.select_items);
        tmphtml.find('input.phone').mask('9999999999',{placeholder:""});
        tmphtml.find('input.dob').mask('9999/99/99',{placeholder:""});
        tmphtml.find('input.int').bind('keypress',ui_ctrl.Num_Input_Mask);
        tmphtml.find('input.float').bind('keypress',ui_ctrl.Float_Input_Mask);
        tmphtml.find('.chk_frame').bind("click keydown",ui_ctrl.check_items);
        
        tmphtml.find(".inputframe[type='check']").each(function(i,o){
          var value = $(o).find("input.check").val();
          $(o).find(".chk_frame[val='"+value+"']").addClass("checked");
        })
        tmphtml.find(".ddframe").each(function(i,o){
          var value = $(o).find("input.dd").val();
          if(value)$(o).find("span.ddind").text($(o).find("a[rep='"+value+"']").text());
        })
        tmphtml.find('.field_value').bind("input keyup",function(e){
          if($(this).val()!=$(this).attr("pre_v"))this_obj.find(".info-save").addClass('active');
        })
      },
      wraphtmlcontent:
      {
        _addbox:function(e,html)
        {
          this_obj.append("")
        }
      },
      get_role_master:function(target,tid)
      {
        preID[target] = tid;
        console.log(target,tid)
        server_exchange("commajax/get_role_master",{target:target,tid:tid,fid:FID},function(){
        console.log(this)
          prevent_history_recall = 0;
          this_obj.find("#main-container").empty();
          var tmphtml = $(this.html);
          this_obj.find("#main-container").append(tmphtml);
          tmphtml.find(".selfie-inside img").attr({width:"",height:""}).css("width","100%");
          
          tmphtml.find(".d-navi-tabs").bind("click",function(){
            if($(this).hasClass("active"))return false;
            $(this).parent().find(".d-navi-tabs.active").removeClass("active");
            ui_ctrl.get_role_detail(this.id,target,tid);
            $(this).addClass("active");
          })
          tmphtml.find(".d-navi-tabs").eq(0).trigger("click");
        },function(){
//          window.location = "";
        })
      },
      get_role_detail:function(type,role,tid)
      {
        console.log(type,role,tid,this)
        preID[role] = tid;
        server_exchange("commajax/get_role_detail",{type:type,target:role,tid:tid,fid:FID},function(){
        console.log(this)
          var rtn_obj = this;
          prevent_history_recall = 0;
          this_obj.find("#detail_info_frame").remove();
          var tmphtml = $(this.html);
          this_obj.find("#main-container").append(tmphtml);
          ui_ctrl.bind_input_event(tmphtml);
          
          tmphtml.find("#save.bt").bind("click",function(){
            prevent_history_recall = 1;
            server_comm.save_material.call(this,tmphtml.find(".infotable"),tid,function(){
              if(this==false)return false;
              var rtn_obj = this;
              tmphtml.hide();
              sys_msg("",this.msg,function(){
                if(rtn_obj.result!="success"){
                  tmphtml.show();
                }
                else{
                  $("#freeze_body").remove();
                  tmphtml.remove();
                  $(".master-navi-icon#"+current_stage).trigger("click");
                }
              });
            },type,FID)
          })
          
          
          
          
          tmphtml.fadeIn(400,'linear',function(){
            if(type=="chartinfo")GetLineChart(rtn_obj.profile,rtn_obj.chart_data,tmphtml.find("#chart-frame .plot"))
          });
        },function(){
//          window.location = "";
        })
      },
      add_material:function(e)
      {
        var obj = $(this);
        if(obj.hasClass("clicking"))return false;
        obj.addClass("clicking");
        server_exchange("commajax/add_material",{target:e.data.target},function(){
          var tmphtml = $(this.html);
          this_obj.append("<div id='freeze_body'/>",tmphtml);
          var box_h = parseInt(tmphtml.find(".blk1").css("padding-top")) + parseInt(tmphtml.find(".blk1").css("padding-bottom")) + tmphtml.find(".blk2").height();
          tmphtml.find(".blk1 tr").each(function(i,o){
            box_h += $(o).find("td").eq(0).height();
          })
          tmphtml.height(box_h);
          tmphtml.find(".g_bt#cancel").bind("click",function(){tmphtml.remove();$("#freeze_body").remove();});
          tmphtml.find(".g_bt#cfn").bind("click",function(){
            prevent_history_recall = 1;
            server_comm.save_material.call(this,tmphtml.find(".infotable"),null,function(){
              if(this==false)return false;
              var rtn_obj = this;
              tmphtml.hide();
              sys_msg("",this.msg,function(){
                if(rtn_obj.result!="success"){
                  tmphtml.show();
                }
                else{
                  $("#freeze_body").remove();
                  tmphtml.remove();
                  $(".master-navi-icon#"+current_stage).trigger("click");
                }
              });
            })
          })
          
          ui_ctrl.bind_input_event(tmphtml);
          tmphtml.fadeIn(250);
          obj.removeClass("clicking");
        },function(){
          window.location = "";
        },false);
      },
      main_navi:function(e)
      {
        e.preventDefault();
        if(e.stopPropagation){e.stopPropagation();}else{e.cancelBubble = true;}
        if(this_obj.find("#wcircle-content").hasClass("wcircle-animating"))return false;
        this_obj.find("#activenow").attr("target",this.id);
        this_obj.find("#wcircle-content").addClass("wcircle-animating");
        this_obj.find('#wcircle-content').WCircleMenu('close');
        current_stage = this.id;
        if(this.id!="home")window.location.href = "#ALLNAVI_" + this.id;
        else window.location.href = "";
        server_exchange(this.id,{controller:this.id,fid:FID},function(){
        //console.log(this)
          this_obj.find("#main-container").empty();
          var tmphtml = $(this.html);
          this_obj.find("#main-container").append(tmphtml);
          tmphtml.find(".action").bind("click",function(){
            window.location.href = $(this).parent().find(".action a").eq(0).attr("href");
            ui_ctrl.get_role_master(current_stage,$(this).parents(".s-tr").attr("idno"));
          })
          tmphtml.find(".addnew_bt").bind("click",{target:current_stage},ui_ctrl.add_material);
          tmphtml.find(".w-blk.op").bind("click",{target:current_stage},ui_ctrl.mnavi_get_option);
          if(!this_obj.find("#wcircle-content").hasClass("wcircle-open"))this_obj.find("#wcircle-content").removeClass("wcircle-animating");
        },function(){window.location = "";})
      },
      mnavi_get_option:function(e)
      {
        this_obj.find("#mnavi-option").remove();
        server_exchange("commajax/navi_table_option",{target:e.data.target,tid:$(this).parents(".s-tr").eq(0).attr("idno"),fid:FID},function(){
        console.log(this)
          var tmphtml = $("<div id='mnavi-option'/>");
          var browserHeight = document.documentElement.clientHeight;
          
          for(var i in this.action){
            if(this.action[i][0]=="sendmail")
              tmphtml.append("<a href='mailto:"+this.staffInfo.email+"' class='action_item' id='"+this.action[i][0]+"'>"+this.action[i][1]+"</a>");
            else
              tmphtml.append("<span class='action_item' id='"+this.action[i][0]+"'>"+this.action[i][1]+"</span>");
          }
          tmphtml.find("#sendauthmail.action_item").bind("click",{uid:this.staffInfo.user_id},server_comm.send_auth_mail)
          
          
          this_obj.append(tmphtml);
          var offsetX = tmphtml.width()+parseInt(tmphtml.css("padding-left"))+parseInt(tmphtml.css("padding-right"));
          var offsetY = tmphtml.height()+parseInt(tmphtml.css("padding-top"))+parseInt(tmphtml.css("padding-bottom"));
          tmphtml.css({"left":e.pageX-offsetX,"top":e.pageY})
          if((parseInt(tmphtml.css("top"))+tmphtml.height())>browserHeight){tmphtml.css({"left":e.pageX-offsetX,"top":e.pageY-offsetY})}
          tmphtml.fadeIn(100);
        },function(){window.location = "";})
        
        
        
        
        
      }
      
    }
    
    
    
    
    
    init();
    
    function init()
    {
      $.ajaxSetup({headers: {'X-CSRF-TOKEN': $('meta[name="csrf-token"]').attr('content')}});
      this_obj.find('#wcircle-content').WCircleMenu({
        width: '3px',
        height: '3px',
        angle_start : -360/this_obj.find(".master-navi-icon").length,
        delay: 100,
        distance: 105,
        angle_interval: 2/this_obj.find(".master-navi-icon").length*Math.PI,
        easingFuncShow:"easeOutBack",
        easingFuncHide:"easeInBack",
        step:10,
        openCallback:false,
        closeCallback:function(){this_obj.find("#wcircle-content").removeClass("wcircle-animating")},
        itemRotation:0,
      });
      this_obj.find(".master-navi-icon").bind("click",ui_ctrl.main_navi);
      this_obj.find("#ls-container #wcircle-content").naviboard_move({move_target:this_obj.find("#ls-container"),reverse:1});
    
    
    
    
      $(document).bind('click',function(e){
        if(e.target!=this_obj.find("#mnavi-option")[0]&&this_obj.find("#mnavi-option").length&&!($(e.target).hasClass("op")&&$(e.target).hasClass("w-blk"))){
          this_obj.find("#mnavi-option").remove();
        }
      });
    }
    
  })
}



})(jQuery);