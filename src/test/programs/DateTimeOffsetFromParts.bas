#procedure
sub Main()
    dim zone = TimeZoneFromName("America/Chicago")
    print DateTimeOffsetFromParts(2021, 3, 12, 4, 30, 0, 0, zone)
end sub
--output--
2021-03-12 04:30:00.000 -06:00
