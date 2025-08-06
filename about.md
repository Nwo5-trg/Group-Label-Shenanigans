# Group Label Shenanigans
adds group labels to more objects, some customization options, makes them not rotate, yk, shenanigans

***you dont get named editor groups support until its mod dev fixes it for mac, if ur a windows dev make a pr or smth idk***

## JSON
u can customize label types further with json

json goes in geodes config folder, in a folder named **"nwo5.group_labels"** (click the folder icon in the geode menu and if you dont see a folder called **"config"** go back 1 folder in the hierarchy then u should see it)

the json is formatted like so

```
// label-types.json

{
    "OBJECT ID": {
        "type": "TYPE"
    },
    "OBJECT ID": {
        "type": "TYPE"
    }
}
```

valid types are:
- "center"
- "target_center"
- "target-center"
- "item"
- "item_anim"
- "anim_target-center"
- "target-center_item-item2"
- "target_item-item2"
- "item_target"
- "target_item"
- "gradient"
- "enter"
- "sfx"
- "color"
- "pulsecolor"
- "blacklist" (adds the trigger to the blacklist, meaning group labels wont show for this trigger)

anything without any entry defaults to just showing target group

type names are formatted like topleft-topright_bottomleft-bottomright, if theres only one on either the top or bottom its centered, if not theyre side by side

btw there are presets for more detail and vanilla in the github repo in a folder called presets

## Credits
- ***farp3*** for the no rotate idea
- ***sandboxer*** for the *"add group labels to stuff that should really have group labels but dont for some reason"* idea

## Quote
***"*** *this is one of those suggestions where people go "i think the new car from 2.2 should have windows on the doors" and i go "what the fuck do you mean the new car from 2.2 doesn't already have windows on the doors" and then i check and it turns out indeed the new car from 2.2 has no windows on the doors* ***"*** - ***HJfod***