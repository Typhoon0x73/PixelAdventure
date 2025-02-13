#coding:utf-8

from xml.etree import ElementTree

import sys
import codecs

# 引数用定義
ARG_DRAWIO_FILE_PATH=u'drawio_path='
ARG_EXPORT_FILE_PREFIX=u'export_prefix='
ARG_EXPORT_DIR=u'export_dir='


if __name__ == u'__main__':
    '''
    エントリーポイント
    '''
    
    # 引数用変数
    drawio_file_path = None
    export_file_prefix = u'_'
    export_dir = u'.'

    # 引数の解析
    for arg in sys.argv:
        if arg.startswith(ARG_DRAWIO_FILE_PATH):
            drawio_file_path = arg[len(ARG_DRAWIO_FILE_PATH):]
            continue
        if arg.startswith(ARG_EXPORT_FILE_PREFIX):
            export_file_prefix = arg[len(ARG_EXPORT_FILE_PREFIX):]
            continue
        if arg.startswith(ARG_EXPORT_DIR):
            export_dir = arg[len(ARG_EXPORT_DIR):]
            continue
    
    # 指定ファイルがなければ、終了。
    if drawio_file_path is None:
        print(u'drawio file path is None.')
        print(u'example arg: drawio_file_path="file path"')
        sys.exit(0)
    
    # xmlファイルを解析。
    tree_data = ElementTree.parse(drawio_file_path)
    xml_root = tree_data.getroot()

    # ページごとに出力処理する。
    for diagram_root in list(xml_root):
        model_root = list(diagram_root)[0]
        data_root = list(model_root)[0]
        cells = list(data_root)

        # ページの設定を取得。
        host_id = xml_root.attrib[u'host']
        diagram_id = diagram_root.attrib[u'id']
        page_name = diagram_root.attrib[u'name']
        window_size_w = model_root.attrib[u'pageWidth']
        window_size_h = model_root.attrib[u'pageHeight']

        export_data_str = u'"{}","{}"\n'.format(host_id, diagram_id)
        export_data_str += u'"{}"\n'.format(page_name)
        export_data_str += u'"layout_size",{},{}\n'.format(window_size_w, window_size_h)

        # 各データを取得。
        for cell in cells:
            # id 0, 1 はvalueアトリビュートがない。
            if not u'value' in cell.attrib:
                continue

            # valueは{データ型_}{名前}の形式で設定している想定。
            cell_name = cell.attrib[u'value']
            if len(cell_name) <= 0:
                continue
            
            # データ型ごとに出力処理をする。
            cell_data = list(cell)[0]
            if cell_name.startswith(u'rect_'):
                data_x = cell_data.attrib[u'x']
                data_y = cell_data.attrib[u'y']
                data_w = cell_data.attrib[u'width']
                data_h = cell_data.attrib[u'height']
                export_data_str += u'"{}",0,{},{},{},{}\n'.format(cell_name[len(u'rect_'):], data_x, data_y, data_w, data_h)

            elif cell_name.startswith(u'point_'):
                data_x = cell_data.attrib[u'x']
                data_y = cell_data.attrib[u'y']
                export_data_str += u'"{}",1,{},{}\n'.format(cell_name[len(u'point_'):], data_x, data_y)
        
        # {prefix}{ページ名}.csvのファイルに書き出す。
        with codecs.open(u'{}/{}{}.csv'.format(export_dir, export_file_prefix, page_name), u'w', u'utf-8') as f:
            f.write(export_data_str)