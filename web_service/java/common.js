// $(function() {
 function server_exchange(url,data,success,error,async){
   async = !async?true:false;
   $.extend(data,{timeoffset:new Date().getTimezoneOffset()});
   $.ajax({
    url: url,
    type: 'post',
    dataType:'json',
    data:data,
    async:async,
    success: function(msg){
      clearloading_animation();
      if(msg.UserIsDeactivate){
        sys_msg("",msg.rtm,function(){
          window.location.href = msg.url;
        });
        return false;
      }
      if(typeof(success)==='function')success.call(msg);
    },
    error:function(msg){
      clearloading_animation();
      if(typeof(error)==='function')error.call(msg);
    }
  })
 }
function loading_animation()
{
//  if (!$("#block_screen_outside").length)
//    $("<div style='background-image:url(\"Image/loading/2675948.gif);' id='block_screen_outside'><div id='block_screen'></div></div>").appendTo($("body"));
}
function clearloading_animation()
{
//  setTimeout(function(){$("#block_screen_outside").remove();},200);
}

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
// })