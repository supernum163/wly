library(inline)
inc <- '#include </home/wly/wly/docs/test.h>'

src <- '
  printf("%d\\n", x->sxpinfo.obj );
'
f <- cxxfunction(signature(x="any"), 
                   includes = inc,
                   src, plugin="Rcpp")

x<-(list(a = 1, b = 2))
f(x)




