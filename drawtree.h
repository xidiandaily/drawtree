#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

#ifndef __H_DRAWTREE_H__
#define __H_DRAWTREE_H__

#define STR_BEGEN "\n\
<html>\n\
  <head>\n\
    <script type='text/javascript' src='https://www.google.com/jsapi'></script>\n\
    <script type='text/javascript'>\n\
      google.load('visualization', '1', {packages:['orgchart']});\n\
      google.setOnLoadCallback(drawChart);\n\
      function drawChart() {\n\
        var data = new google.visualization.DataTable();\n\
        data.addColumn('string', 'Name');\n\
        data.addColumn('string', 'Manager');\n\
        data.addColumn('string', 'ToolTip');\n\
        data.addRows([\n\
              "
#define STR_END "\n\
        ]);\n\
        var chart = new google.visualization.OrgChart(document.getElementById('chart_div'));\n\
        chart.draw(data, {allowHtml:true});\n\
      }\n\
    </script>\n\
  </head>\n\
\n\
  <body>\n\
    <div id='chart_div'></div>\n\
  </body>\n\
</html>"

typedef struct node{
    int id;

    struct node* left;
    struct node* right;
}T_NODE;

typedef enum{
    UNSHOW_NULL,
    SHOW_NULL
}DRAW_TYPE;

bool drawtree_build_googleAPI_html(T_NODE* head,DRAW_TYPE type,char* filename);
#endif
