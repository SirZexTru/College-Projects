<?php

namespace App\Util;

class Csv
{
    public static function read($csvFile)
    {
        $data = [];

        $csv = is_file($csvFile) ? fopen($csvFile, 'r') : null;

        if (is_resource($csv)) {
            while (!feof($csv)) {
                $row = fgetcsv($csv, null, ',');
                if ($row && !$row[0] == null) {
                    $data[] = $row;
                }
            }

            fclose($csv);
        }

        return $data;
    }

    public static function createCsv($data, $header = [], $sep = ';')
    {
        $body = '';

        if (!empty($header)) {
            if (isset($data[0]) && sizeof($header) != sizeof($data[0])) {
                throw new \InvalidArgumentException('The elements od header are different from the body');
            }

            $body .= '"' . implode('"' . $sep . '"', $header) . "\"\n";
        }

        foreach ($data as $row) {
            $row = str_replace('<br>', " :: ", $row);

            $body .= '"' . implode('"' . $sep . '"', $row) . "\"\n";
        }

        return $body;
    }
}
