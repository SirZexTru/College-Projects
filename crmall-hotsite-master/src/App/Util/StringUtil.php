<?php

namespace App\Util;

class StringUtil
{
    public static function numbersOnly($string)
    {
        return preg_replace('/[^0-9]/', '', $string);
    }


    public static function withoutAccent($string)
    {
        $string = strtolower($string);

        $from = array('Á', 'Í', 'Ó', 'Ú', 'É', 'Ä', 'Ï', 'Ö', 'Ü', 'Ë', 'À', 'Ì', 'Ò', 'Ù', 'È', 'Ã', 'Õ', 'Â', 'Î', 'Ô', 'Û', 'Ê', 'á', 'í', 'ó', 'ú', 'é', 'ä', 'ï', 'ö', 'ü', 'ë', 'à', 'ì', 'ò', 'ù', 'è', 'ã', 'õ', 'â', 'î', 'ô', 'û', 'ê', 'Ç', 'ç');
        $to = array('A', 'I', 'O', 'U', 'E', 'A', 'I', 'O', 'U', 'E', 'A', 'I', 'O', 'U', 'E', 'A', 'O', 'A', 'I', 'O', 'U', 'E', 'a', 'i', 'o', 'u', 'e', 'a', 'i', 'o', 'u', 'e', 'a', 'i', 'o', 'u', 'e', 'a', 'o', 'a', 'i', 'o', 'u', 'e', 'C', 'c');

        $string = preg_replace('/[^a-zA-Z0-9_-]/', '', str_replace($from, $to, $string));

        return $string;
    }

    public static function toAlphaNumeric($string)
    {
        $string = strtolower(trim($string));

        $from = array('Á', 'Í', 'Ó', 'Ú', 'É', 'Ä', 'Ï', 'Ö', 'Ü', 'Ë', 'À', 'Ì', 'Ò', 'Ù', 'È', 'Ã', 'Õ', 'Â', 'Î', 'Ô', 'Û', 'Ê', 'á', 'í', 'ó', 'ú', 'é', 'ä', 'ï', 'ö', 'ü', 'ë', 'à', 'ì', 'ò', 'ù', 'è', 'ã', 'õ', 'â', 'î', 'ô', 'û', 'ê', 'Ç', 'ç', ' ', '_');
        $to = array('A', 'I', 'O', 'U', 'E', 'A', 'I', 'O', 'U', 'E', 'A', 'I', 'O', 'U', 'E', 'A', 'O', 'A', 'I', 'O', 'U', 'E', 'a', 'i', 'o', 'u', 'e', 'a', 'i', 'o', 'u', 'e', 'a', 'i', 'o', 'u', 'e', 'a', 'o', 'a', 'i', 'o', 'u', 'e', 'C', 'c', '-', '-');

        $string = preg_replace('/[^a-zA-Z0-9_-]/', '', str_replace($from, $to, $string));

        return trim($string, '-');
    }

    /**
     * Source:
     * @link https://gist.github.com/jeremiahlee/2885845
     *
     * @param $date
     * @return false|int
     */
    public static function assertISO8601Date($date)
    {
        return (bool)preg_match('/^([\+-]?\d{4}(?!\d{2}\b))((-?)((0[1-9]|1[0-2])(\3([12]\d|0[1-9]|3[01]))?|W([0-4]\d|5[0-2])(-?[1-7])?|(00[1-9]|0[1-9]\d|[12]\d{2}|3([0-5]\d|6[1-6])))([T\s]((([01]\d|2[0-3])((:?)[0-5]\d)?|24\:?00)([\.,]\d+(?!:))?)?(\17[0-5]\d([\.,]\d+)?)?([zZ]|([\+-])([01]\d|2[0-3]):?([0-5]\d)?)?)?)?$/', $date);
    }

    public static function mask($val, $mask)
    {
        $val = self::numbersOnly($val);

        $withMask = '';
        $k = 0;
        for ($i = 0; $i <= strlen($mask) - 1; ++$i) {
            if ($mask[$i] == '#') {
                if (isset($val[$k])) {
                    $withMask .= $val[$k++];
                }
            } else {
                if (isset($mask[$i])) {
                    $withMask .= $mask[$i];
                }
            }
        }

        return $withMask;
    }
}
