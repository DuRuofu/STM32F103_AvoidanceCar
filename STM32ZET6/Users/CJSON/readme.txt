cJSON是一个轻量级的C语言库，用于解析和生成JSON数据。它提供了简单、高效的方法来处理JSON数据，无需依赖其他复杂的数据结构或外部库。

以下是关于cJSON的一些重要特性和用法说明：

简单易用：cJSON提供了简洁明了的API，使得解析和生成JSON数据变得非常容易。

解析JSON：使用cJSON_Parse()函数可以将JSON字符串解析为cJSON对象。解析后的对象可以访问和操作JSON数据的各个部分。

访问JSON数据：通过cJSON对象，可以使用各种API函数来访问JSON数据的不同元素，如对象、数组、字符串、数字等。

生成JSON：使用cJSON_CreateObject()、cJSON_CreateArray()和其他相关函数，可以创建cJSON对象来构建JSON数据。然后，使用cJSON_Print()函数将cJSON对象转换为JSON字符串。

修改JSON数据：通过修改cJSON对象，可以更新JSON数据的内容、添加新的元素或删除现有元素。

序列化和反序列化：cJSON支持将JSON数据序列化为字符串，并将字符串反序列化为cJSON对象，方便存储、传输和处理JSON数据。

跨平台：cJSON是一个纯C语言库，可以在各种操作系统和平台上使用。

下面是一个简单示例，展示了如何使用cJSON解析和生成JSON数据：

--------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "cJSON.h"

int main() {
    // 解析JSON字符串
    char json[] = "{\"name\":\"Alice\",\"age\":25,\"city\":\"Beijing\"}";
    cJSON *root = cJSON_Parse(json);
    if (root == NULL) {
        printf("JSON解析失败：%s\n", cJSON_GetErrorPtr());
        return 1;
    }

    // 访问JSON数据
    cJSON *name = cJSON_GetObjectItemCaseSensitive(root, "name");
    if (cJSON_IsString(name)) {
        printf("Name: %s\n", name->valuestring);
    }

    cJSON *age = cJSON_GetObjectItemCaseSensitive(root, "age");
    if (cJSON_IsNumber(age)) {
        printf("Age: %d\n", age->valueint);
    }

    cJSON *city = cJSON_GetObjectItemCaseSensitive(root, "city");
    if (cJSON_IsString(city)) {
        printf("City: %s\n", city->valuestring);
    }

    // 生成JSON字符串
    cJSON *newRoot = cJSON_CreateObject();
    cJSON_AddStringToObject(newRoot, "fruit", "apple");
    cJSON_AddNumberToObject(newRoot, "quantity", 5);
    char *newJson = cJSON_Print(newRoot);

    printf("Generated JSON: %s\n", newJson);

    // 释放内存
    cJSON_Delete(root);
    cJSON_Delete(newRoot);
    free(newJson);

    return 0;
}
--------------------------------------------------------------------------------------------------------


这个示例代码演示了如何使用cJSON库来解析一个JSON字符串，访问其中的数据，并生成一个新的JSON字符串。


下面是源代码地址：https://github.com/DaveGamble/cJSON#zero-character


2023.7.22  DuRuofu