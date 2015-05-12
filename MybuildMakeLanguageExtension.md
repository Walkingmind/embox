Поскольку синтаксис языка Make достаточно бедный, в Mybuild используются средства для его расширения, добавляющие такие возможности, как:

  * Использование многострочных функций, индентации и комментариев внутри тела функций
  * Определение анонимных функций внутри другой функции
  * ...

> <table width='839' cellspacing='10'><tr valign='top'><td width='50%'>
<blockquote><h2>Без расширений</h2>
<pre><code>foo = \<br>
	$(foreach bar,x y z, \<br>
		$(call baz,$(bar)))<br>
</code></pre>
</td><td>
<h2>С расширениями</h2>
<pre><code>define foo<br>
	$(for bar &lt;- x y z,<br>
		# Some comments...<br>
		$(call baz,$(bar)))<br>
endef<br>
</code></pre>
</td></tr></table></blockquote>

## объектно ориентированная надстройка ##
Позволяет определять классы, их свойства и методы, а также создавать объекты и обращаться к ним.

```
define class-Foo
	$(field message,$1)
	$(method sayHello,
		$(info $(get-field message)))
endef
```
```
define some_func
	$(for foo <- $(new Foo,Privet!),
		$(invoke foo->sayHello)
		# Return the instance.
		$(foo))
endef
```