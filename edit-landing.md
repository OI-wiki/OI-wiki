disqus:
# 编辑前须知

首先，感谢您能够为 [OI-wiki](https://oi-wiki.org) 做出自己的贡献。

不过在开始之前，我们需要您了解并熟知[如何参与](../../intro/htc.md)里的内容，以在提交 Pull Request 时避免不必要的麻烦。        

在阅读完之后，请点击下方的按钮，然后去 `Edit` 处编辑。



<button id="btn_startedit" style="padding: 0.75em 1.25em; display: inline-block; line-height: 1; text-decoration: none; white-space: nowrap; cursor: pointer; border: 1px solid #6190e8; border-radius: 5px; background-color: #6190e8; color: #fff; outline: none; font-size: 0.75em;">开始编辑</button>
<script>
function getQueryVariable(variable)
{
       var query = window.location.search.substring(1);
       var vars = query.split("&");
       for (var i=0;i<vars.length;i++) {
               var pair = vars[i].split("=");
               if(pair[0] == variable){return pair[1];}
       }
       return(false);
}
document.getElementById("btn_startedit").addEventListener("click", function(){
window.location.href="https://github.com/OI-wiki/OI-wiki/blob/master/docs/"+getQueryVariable("ref");
}, false);
</script>