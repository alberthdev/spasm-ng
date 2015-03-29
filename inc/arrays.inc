#IFNDEF ARRAY_INC
#DEFINE ARRAY_INC

#macro new_array(name)
  #define str_name concat("\"",name,"\"")

  clr()
  wr("#define ",str_name,"(ind)  #define zind concat(\"ind\")\\ clr()\\ wr(\"#define ",str_name,"(ind) \\\\ #define zind concat(\\\"ind\\\")\\ #if zind=\",zind,\"\\\\ ",str_name,"\",zind,\"\\\\ #else\\\\",str_name," #endif\\\\\")\\ wr(\"\\\\",str_name,"\",zind)\\ #undefine zind\\ run()\\\")
  run()
#endmacro

#ENDIF
