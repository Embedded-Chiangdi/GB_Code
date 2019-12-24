# HTML Note
Here are some html codes for my bussiness project which really practical.
## Example 1
根据不同的select 下拉选择显示不同的文本框
```javascript
<!DOCTYPE HTML>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<meta name="author" content="http://www.softwhy.com/" />
<title>根本不同的select下拉选项显示不同的文本框</title>
<style type="text/css">
input{display:none}
</style>
<script type="text/javascript"> 
function $(obj){
  return document.getElementById(obj);
} 
function show(objid){
  $(objid).style.display='inline';
} 
function hidden(objid){
  $(objid).style.display='none';
} 
function doit(){ 
  var sel_val=$('iptables_mode_id').value; 
  if(sel_val==0){
    show('mode1');
    hidden('mode2');
  } 
  if(sel_val==1){
    show('mode2');hidden('mode1');
  } 
  if(sel_val==2){
    show('mode1');
    show('mode2');
  } 
} 
window.onload=function(){
  var sel=document.getElementById("iptables_mode_id");
  sel.onchange=doit;
}
</script> 
</head>
<body> 
<select name="iptables_mode" id="iptables_mode_id"> 
  <option value="0">IP模式</option> 
  <option value="1">PORT模式</option> 
  <option value="2">IP+PORT模式</option> 
</select> 
<input value="IP" type="text" id="mode1"/> 
<input value="PORT" type="text" id="mode2" /> 
</body> 
</html>
```
***
摘自[蚂蚁部落](http://www.softwhy.com/article-8100-1.html)
***