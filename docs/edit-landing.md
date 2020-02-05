disqus:

# 编辑前须知

首先，感谢您能够为 **OI Wiki** 做出自己的贡献。

不过在开始之前，我们需要您了解并熟知 [如何参与](./intro/htc.md) 里的内容，以避免在编辑时产生不必要的麻烦。

在阅读完之后，请点击下方的按钮，然后开始编辑。

<a id="btn-startedit" style="padding: 0.75em 1.25em; display: inline-block; line-height: 1; text-decoration: none; white-space: nowrap; cursor: pointer; border: 1px solid #6190e8; border-radius: 5px; background-color: #6190e8; color: #fff; outline: none; font-size: 0.75em;">开始编辑</a>

<script>
	function getQueryVariable(name, dft)
	{
		var reg = new RegExp('(^|&)' + name + '=([^&]*)(&|$)', 'i');
		var r = window.location.search.substr(1).match(reg);
		if (r != null)
		{
			return unescape(r[2]);
		}
		return dft;
	}
	document.getElementById("btn-startedit").href = "https://github.com/OI-wiki/OI-wiki/edit/master/docs" + getQueryVariable("ref", "");
</script>
