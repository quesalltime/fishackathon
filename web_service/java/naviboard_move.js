(function ($){
$.extend($.naviboard_move,{
  extend : function(methods) {
    $.extend($.fn.naviboard_move,methods);
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
$.fn.naviboard_move = function(pin) {
  if (typeof pin == 'string') {
    var fn = $.naviboard_move.getAccessor($.fn.naviboard_move,pin);
    if (!fn) {throw ("No such method: " + pin);}
    var args = $.makeArray(arguments).slice(1);
    return fn.apply(this,args);
  }
  return this.each(function(){
    var this_obj = $(this);
    var pdx = 0;
    var pdy = 0;
    var obj_positionX = 0;
    var obj_positionY = 0;
    var move_target = pin.move_target;
    var reverse = pin.reverse;
    
    init();
    function init()
    {
      this_obj.bind("mousedown",start);
      this_obj[0].ontouchstart = function(e){
        this_obj.unbind('mousedown');
        start(e.touches[0]);
      };
      
    }
    function start(e)
    {
      pdx = e.pageX;
      pdy = e.pageY;
      if(reverse==1){
        obj_positionX = parseInt(move_target.css("right"));
        obj_positionY = parseInt(move_target.css("bottom"));
      }
      else{
        obj_positionX = parseInt(move_target.css("left"));
        obj_positionY = parseInt(move_target.css("top"));
      }
      this_obj.removeClass("mouse-moving");
      this_obj.bind('mousemove',move);
      $(document).bind('mousemove',move);
      this_obj.bind('mouseup',end);
      document.ontouchmove = function(oEvent){
        oEvent.preventDefault();
        $(document).unbind('mousemove');
        move(oEvent.touches[0]);
      };
      this_obj[0].ontouchend = document.ontouchend = function(e){
        $(document).unbind('mouseup');
        this_obj.unbind('mouseup');
        end(e.touches[0]);
      };
    }
    function move(e)
    {
      this_obj.addClass("mouse-moving");
      if(reverse==1){
        move_target.css("right",obj_positionX-(e.pageX-pdx))
        move_target.css("bottom",obj_positionY-(e.pageY-pdy))
      }
      else{
        move_target.css("left",obj_positionX-(pdx-e.pageX))
        move_target.css("top",obj_positionY-(pdy-e.pageY))
      }
    }
    function end(e)
    {
      this_obj.unbind('mousemove');
      this_obj.unbind('mouseup');
      $(document).unbind('mousemove');
      document.ontouchmove = this_obj[0].ontouchend = document.ontouchend = null;
    }
  })
}
  
  
  
})(jQuery);


