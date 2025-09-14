#!/bin/bash

output="app_assets.qrc"
assets=("Images" "Fonts")

echo "<RCC>" > $output
echo "    <qresource prefix=\"/\">" >> $output

shopt -s globstar
for asset in "${assets[@]}"; do
    for file in $asset/**; do
        if [[ -f "$file" ]] then
            echo "        <file>$file</file>" >> $output
        fi
    done
done

echo "    </qresource>" >> $output
echo "</RCC>" >> $output
